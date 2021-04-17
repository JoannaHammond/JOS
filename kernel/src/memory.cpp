
#pragma GCC optimize("Ofast")//,"unroll-loops","inline") //Optimization flags
#pragma GCC target("sse")  //Enable sse

#include "memory.h"

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize){

    static uint64_t memorySizeBytes = 0;
    if (memorySizeBytes > 0) return memorySizeBytes;

    for (uint64_t i = 0; i < mMapEntries; i++){
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        memorySizeBytes += desc->numPages * 4096;
    }

    return memorySizeBytes;

}

void memVectorCopy(uint64_t *dest, uint64_t *src, unsigned long length)
{
     for (unsigned long n=0; n < length; n++){
        dest[n] = src[n];
    }
}