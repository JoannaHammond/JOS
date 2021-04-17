#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit/pit.h"
#include "panic.h"
#include "memory.h"

extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);

    GlobalRenderer->Print("PageTableManager @");
    GlobalRenderer->Println(to_hstring((uint64_t)kernelInfo.pageTableManager));

    GlobalRenderer->Print("Memory Size: ");
    GlobalRenderer->Print(to_string(GetMemorySize(bootInfo->mMap, bootInfo->mMapSize / bootInfo->mMapDescSize, bootInfo->mMapDescSize)/1024));
    GlobalRenderer->Println(" KB");

    GlobalRenderer->Print("Free Memory : ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetFreeRAM()/1024));
    GlobalRenderer->Println(" KB");

    GlobalRenderer->Print("Reserved Memory : ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetReservedRAM()/1024));
    GlobalRenderer->Println(" KB");

    GlobalRenderer->Print("Used Memory : ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetUsedRAM()/1024));
    GlobalRenderer->Println(" KB");

    GlobalRenderer->Print("Largest Contiguos Block size : ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetLargestFreeMemSegSize()/1024));
    GlobalRenderer->Println(" KB");

    for(uint64_t i = 0 ; i < 8000000; i++)
    {
        PIT::Sleepd(1);
        GlobalRenderer->Print("Testing ");
        GlobalRenderer->Println(to_string(i));
    }

    PIT::Sleepd(60);


    Panic("TEST PANIC");

    while(true){
        asm ("hlt");
    }

}