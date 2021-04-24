#include "kernelUtil.h"
#include "gdt/gdt.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupts.h"
#include "IO.h"
#include "memory/heap.h"
#include "scheduling/pit/pit.h"
#include "paging/PageTableManager.h"
#include "cstr.h"
#include "utils/print.h"
#include "rendering/Canvas.h"
#include "rendering/TextCanvas.h"
#include "rendering/ImageCanvas.h"

KernelInfo kernelInfo; 

void PrepareMemory(BootInfo* bootInfo){

    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    GlobalAllocator = PageFrameAllocator();
    GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

    PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
    memset(PML4, 0, 0x1000);

    g_PageTableManager = PageTableManager(PML4);

    for (uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); t+= 0x1000){
        g_PageTableManager.MapMemory((void*)t, (void*)t);
    }

    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
    GlobalAllocator.LockPages((void*)fbBase, fbSize/ 0x1000 + 1);
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096){
        g_PageTableManager.MapMemory((void*)t, (void*)t, PAT_WC_MODE);
    }

    asm ("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.pageTableManager = &g_PageTableManager;
}

IDTR idtr;
void SetIDTGate(void* handler, uint8_t entryOffset, uint8_t type_attr, uint8_t selector){

    IDTDescEntry* interrupt = (IDTDescEntry*)(idtr.Offset + entryOffset * sizeof(IDTDescEntry));
    interrupt->SetOffset((uint64_t)handler);
    interrupt->type_attr = type_attr;
    interrupt->selector = selector;
}

void PrepareInterrupts(){
    idtr.Limit = 0x0FFF;
    idtr.Offset = (uint64_t)GlobalAllocator.RequestPage();


    SetIDTGate((void*)DivideByZeroFault_Handler, IRQ_DIVIDE_BY_ZERO, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)BoundRangeExceededFault_Handler, IRQ_BOUND_RANGE_EXCEEDED, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)InvalidOpcodeFault__Handler, IRQ_INVALID_OPCODE, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)DeviceNotAvailableFault__Handler, IRQ_DEVICE_NOT_AVAILABLE, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)InvlalidTSSFault_Handler, IRQ_INVALID_TSS, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)SegmentNotPresentFault_Handler, IRQ_SEGMENT_NOT_PRESENT, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)StackSegmentFault_Handler, IRQ_STACK_SEGMENT_FAULT, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)FloatingPointExceptionFault_Handler, IRQ_FLOATING_POINT_EXCEPTION, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)AlignmentCheckFault_Handler, IRQ_ALIGNMENT_CHECK, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)SIMDFloatingPointExceptionFault_Handler, IRQ_SIMD_FLOATING_POINT_EXCEPTION, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)MachineCheckFault_Handler, IRQ_MACHINE_CHECK, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)VirtualisationExceptionFault_Handler, IRQ_VIRTUALISATION_EXCEPTION, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)SecurityExceptionFault_Handler, IRQ_SECURITY_EXCEPTION, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)PageFault_Handler, IRQ_PAGE_FAULT, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)DoubleFault_Handler, IRQ_DOUBLE_FAULT, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)GPFault_Handler, IRQ_GENERAL_PROTECTION_FAULT, IDT_TA_InterruptGate, 0x08);

    SetIDTGate((void*)KeyboardInt_Handler, 0x21, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)MouseInt_Handler, 0x2C, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)PITInt_Handler, 0x20, IDT_TA_InterruptGate, 0x08);
 
    asm ("lidt %0" : : "m" (idtr));

    RemapPIC();
}

void PrepareACPI(BootInfo* bootInfo){
    ACPI::SDTHeader* xsdt = (ACPI::SDTHeader*)(bootInfo->rsdp->XSDTAddress);
    
    ACPI::MCFGHeader* mcfg = (ACPI::MCFGHeader*)ACPI::FindTable(xsdt, (char*)"MCFG");

    PCI::EnumeratePCI(mcfg);
}

//BasicRenderer r = BasicRenderer(NULL, NULL);
KernelInfo InitializeKernel(BootInfo* bootInfo){
    GlobalRenderer = NULL;
    // These functions are not trapped, no GUI output is possible
    // They have to occur before we can do anything else.
    GDTDescriptor gdtDescriptor;
    gdtDescriptor.Size = sizeof(GDT) - 1;
    gdtDescriptor.Offset = (uint64_t)&DefaultGDT;
    LoadGDT(&gdtDescriptor);
    PrepareMemory(bootInfo);
    PrepareInterrupts();
    InitializeHeap((void*)0x0000100000000000, 0x1);
    // Turn on PIC Interrupt Flags
    outb(PIC1_DATA, 0b11111000);
    outb(PIC2_DATA, 0b11101111);
    // Enable Interrupts.
    asm ("sti");

    memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

    GlobalRenderer = new BasicRenderer(bootInfo->framebuffer);
    TextCanvas* textCanvas = GlobalRenderer->createTextCanvas(1, bootInfo->psf1_Font);
    GlobalPrinter.RegisterTextCanvas(textCanvas);
    ImageCanvas* imageCanvas = new ImageCanvas((bootInfo->framebuffer->PixelsPerScanLine-320)/2,0,320,180,65536,Canvas::OVERLAY_MODE::ADD);
    imageCanvas->SetImage(bootInfo->logoImage);
    GlobalRenderer->getRootCanvas()->AddChildCanvas(textCanvas);
    GlobalRenderer->getRootCanvas()->AddChildCanvas(imageCanvas);
    
    GlobalPrinter.Println("GDT/Memory/Interupts/Heap initialised.");

    InitPS2Mouse();
    GlobalPrinter.Println("Mouse Initialised.");
    PrepareACPI(bootInfo);

    GlobalPrinter.Println("Waiting for 10 seconds.");
    
    return kernelInfo;
}