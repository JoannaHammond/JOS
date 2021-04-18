#include "heap.h"
#include "../paging/PageTableManager.h"
#include "../paging/PageFrameAllocator.h"
#include "../rendering/BasicRenderer.h"
#include "../scheduling/pit/pit.h"
#include "../cstr.h"

void* heapStart;
void* heapEnd;
HeapSegHdr* LastHdr;

void InitializeHeap(void* heapAddress, size_t pageCount){
    void* pos = heapAddress;

    for (size_t i = 0; i < pageCount; i++){
        void* newPage = GlobalAllocator.RequestPage();
        g_PageTableManager.MapMemory(pos, newPage);
        pos = (void*)((size_t)pos + 0x1000);
    }


    size_t heapLength = pageCount * 0x1000;

    heapStart = heapAddress;
    heapEnd = (void*)((size_t)heapStart + heapLength);
    HeapSegHdr* startSeg = (HeapSegHdr*)heapAddress;
    
    startSeg->length = heapLength - sizeof(HeapSegHdr);
    startSeg->next = NULL;
    startSeg->last = NULL;
    startSeg->free = true;
    LastHdr = startSeg;
}

void free(void* address, long unsigned int i)
{
        free(address);
}

void free(void* address){
    //GlobalRenderer->Println("FREE Heap");
    HeapSegHdr* segment = (HeapSegHdr*)address - 1;
    segment->free = true;
    segment->CombineForward();
    segment->CombineBackward();
}

void* malloc(size_t size){

    //GlobalRenderer->Println("MALLOC Heap");
    if (size % 0x10 > 0){ // it is not a multiple of 0x10
        size -= (size % 0x10);
        size += 0x10;
    }

    if (size == 0) return NULL;

    HeapSegHdr* currentSeg = (HeapSegHdr*) heapStart;
    while(true){
        if(currentSeg->free){
            if (currentSeg->length > size){
                currentSeg->Split(size);
                currentSeg->free = false;
                return (void*)((uint64_t)currentSeg + sizeof(HeapSegHdr));
            }
            if (currentSeg->length == size){
                currentSeg->free = false;
                return (void*)((uint64_t)currentSeg + sizeof(HeapSegHdr));
            }
        }
        if (currentSeg->next == NULL) break;
        currentSeg = currentSeg->next;
    }
    //GlobalRenderer->Println("Expanding Heap");
    ExpandHeap(size);
    return malloc(size);
}

HeapSegHdr* HeapSegHdr::Split(size_t splitLength){
    //GlobalRenderer->Println("SPLIT Heap");
    if (splitLength < 0x10) return NULL;
    int64_t splitSegLength = length - splitLength - (sizeof(HeapSegHdr));
    if (splitSegLength < 0x10) return NULL;

    HeapSegHdr* newSplitHdr = (HeapSegHdr*) ((size_t)this + splitLength + sizeof(HeapSegHdr));
    if(next != NULL)
        next->last = newSplitHdr; // Set the next segment's last segment to our new segment
    newSplitHdr->next = next; // Set the new segment's next segment to out original next segment
    next = newSplitHdr; // Set our new segment to the new segment
    newSplitHdr->last = this; // Set our new segment's last segment to the current segment
    newSplitHdr->length = splitSegLength; // Set the new header's length to the calculated value
    newSplitHdr->free = free; // make sure the new segment's free is the same as the original
    length = splitLength; // set the length of the original segment to its new length

    if (LastHdr == this) LastHdr = newSplitHdr;
    return newSplitHdr;
}

void ExpandHeap(size_t length){
    //GlobalRenderer->Println("EXPAND Heap");
    if (length % 0x1000) {
        length -= length % 0x1000;
        length += 0x1000;
    }

    size_t pageCount = length / 0x1000;
    HeapSegHdr* newSegment = (HeapSegHdr*)heapEnd;

    for (size_t i = 0; i < pageCount; i++){
        void* newPage = GlobalAllocator.RequestPage();
        if(newPage == NULL)
        {
            //return;//GlobalRenderer->Println("UNABLE TO REQUEST PAGE <GAME OVER>");
        }
        g_PageTableManager.MapMemory(heapEnd, newPage);
        heapEnd = (void*)((size_t)heapEnd + 0x1000 );
    }

    newSegment->free = true;
    newSegment->last = LastHdr;
    LastHdr->next = newSegment;
    LastHdr = newSegment;
    newSegment->next = NULL;
    newSegment->length = length - sizeof(HeapSegHdr);
    newSegment->CombineBackward();

}

void HeapSegHdr::CombineForward(){
    //GlobalRenderer->Println("CFWD Heap");
    if (next == NULL) return;
    if (!next->free) return;

    if (next == LastHdr) LastHdr = this;

    if (next->next != NULL){
        next->next->last = this;
    }

    

    length = length + next->length + sizeof(HeapSegHdr);

    next = next->next;
}

void HeapSegHdr::CombineBackward(){
    //GlobalRenderer->Println("CBKWD Heap");
    if (last != NULL && last->free) last->CombineForward();
}

