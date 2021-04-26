#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit/pit.h"
#include "panic.h"
#include "memory/memory.h"
#include "utils/math/trig.h"

extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);

    GlobalPrinter.PrintText("PageTableManager @");
    GlobalPrinter.Println(to_hstring((uint64_t)kernelInfo.pageTableManager));

    GlobalPrinter.PrintText("Memory Size: ");
    GlobalPrinter.PrintText(to_string(GetMemorySize(bootInfo->mMap, bootInfo->mMapSize / bootInfo->mMapDescSize, bootInfo->mMapDescSize)/1024));
    GlobalPrinter.Println(" KB");

    GlobalPrinter.PrintText("Free Memory : ");
    GlobalPrinter.PrintText(to_string(GlobalAllocator.GetFreeRAM()/1024));
    GlobalPrinter.Println(" KB");

    GlobalPrinter.PrintText("Reserved Memory : ");
    GlobalPrinter.PrintText(to_string(GlobalAllocator.GetReservedRAM()/1024));
    GlobalPrinter.Println(" KB");

    GlobalPrinter.PrintText("Used Memory : ");
    GlobalPrinter.PrintText(to_string(GlobalAllocator.GetUsedRAM()/1024));
    GlobalPrinter.Println(" KB");

    GlobalPrinter.PrintText("Largest Contiguos Block size : ");
    GlobalPrinter.PrintText(to_string(GlobalAllocator.GetLargestFreeMemSegSize()/1024));
    GlobalPrinter.Println(" KB");

    GlobalPrinter.PrintText("Trig Test Sin(1) =  ");
    GlobalPrinter.Println(to_string((double)sin(1.0)));


    GlobalPrinter.Println("Starting scroll test is 10 seconds.");
    PIT::Sleepd(10);

    for(uint64_t i = 0 ; i < 8000000; i++)
    {
        GlobalPrinter.PrintText("Testing ");
        GlobalPrinter.PrintText(to_string(i));
        GlobalPrinter.PrintText(",  Sin(");
        GlobalPrinter.PrintText(to_string(((double)i)/1000.0));
        GlobalPrinter.PrintText(") = ");
        GlobalPrinter.Println(to_string((double)sin(((double)i)/1000.0)));
    }

    PIT::Sleepd(60);


    Panic("TEST PANIC");

    //memset32(GlobalRenderer->defaultCanvases->textCanvas->GetCanvasInfo()->buffer, 0xffffffff, bootInfo->framebuffer->BufferSize/4);
    while(true){
        asm ("hlt");
    }

}