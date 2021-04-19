#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit/pit.h"
#include "panic.h"
#include "memory.h"

extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);

    /*GlobalRenderer->defaultCanvases.textCanvas->Print("PageTableManager @");
    GlobalRenderer->defaultCanvases.textCanvas->Println(to_hstring((uint64_t)kernelInfo.pageTableManager));

    GlobalRenderer->defaultCanvases.textCanvas->Print("Memory Size: ");
    GlobalRenderer->defaultCanvases.textCanvas->Print(to_string(GetMemorySize(bootInfo->mMap, bootInfo->mMapSize / bootInfo->mMapDescSize, bootInfo->mMapDescSize)/1024));
    GlobalRenderer->defaultCanvases.textCanvas->Println(" KB");

    GlobalRenderer->defaultCanvases.textCanvas->Print("Free Memory : ");
    GlobalRenderer->defaultCanvases.textCanvas->Print(to_string(GlobalAllocator.GetFreeRAM()/1024));
    GlobalRenderer->defaultCanvases.textCanvas->Println(" KB");

    GlobalRenderer->defaultCanvases.textCanvas->Print("Reserved Memory : ");
    GlobalRenderer->defaultCanvases.textCanvas->Print(to_string(GlobalAllocator.GetReservedRAM()/1024));
    GlobalRenderer->defaultCanvases.textCanvas->Println(" KB");

    GlobalRenderer->defaultCanvases.textCanvas->Print("Used Memory : ");
    GlobalRenderer->defaultCanvases.textCanvas->Print(to_string(GlobalAllocator.GetUsedRAM()/1024));
    GlobalRenderer->defaultCanvases.textCanvas->Println(" KB");

    GlobalRenderer->defaultCanvases.textCanvas->Print("Largest Contiguos Block size : ");
    GlobalRenderer->defaultCanvases.textCanvas->Print(to_string(GlobalAllocator.GetLargestFreeMemSegSize()/1024));
    GlobalRenderer->defaultCanvases.textCanvas->Println(" KB");

    GlobalRenderer->defaultCanvases.textCanvas->Println("Starting scroll test is 10 seconds.");
    PIT::Sleepd(10);

    for(uint64_t i = 0 ; i < 8000000; i++)
    {
        GlobalRenderer->defaultCanvases.textCanvas->Print("Testing ");
        GlobalRenderer->defaultCanvases.textCanvas->Println(to_string(i));
    }

    PIT::Sleepd(60);

*/
    Panic("TEST PANIC");

    //memset32(GlobalRenderer->defaultCanvases->textCanvas->GetCanvasInfo()->buffer, 0xffffffff, bootInfo->framebuffer->BufferSize/4);
    while(true){
        asm ("hlt");
    }

}