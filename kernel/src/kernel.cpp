#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit/pit.h"
#include "panic.h"

extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    GlobalRenderer->Print("PageTableManager @");
    GlobalRenderer->Print(to_hstring((uint64_t)kernelInfo.pageTableManager));
    GlobalRenderer->Next();

    GlobalRenderer->Next();
    GlobalRenderer->Print("Free Memory : ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetFreeRAM()/1024));
    GlobalRenderer->Print(" KB");

    GlobalRenderer->Next();
    GlobalRenderer->Print("Reserved Memory : ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetReservedRAM()/1024));
    GlobalRenderer->Print(" KB");

    GlobalRenderer->Next();
    GlobalRenderer->Print("Used Memory : ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetUsedRAM()/1024));
    GlobalRenderer->Print(" KB");

    GlobalRenderer->Next();
    GlobalRenderer->Print("Largest Contiguos Block size : ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetLargestFreeMemSegSize()/1024));
    GlobalRenderer->Print(" KB");


    PIT::Sleepd(10);


    Panic("TEST PANIC");

    while(true){
        asm ("hlt");
    }

}