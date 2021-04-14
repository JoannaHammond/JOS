#include "interrupts.h"
#include "../panic.h"
#include "../IO.h"
#include "../userinput/keyboard.h"
#include "../scheduling/pit/pit.h"

__attribute__((interrupt)) void PageFault_Handler(interrupt_frame* frame){
    Panic("Page Fault Detected");
    while(true);
}

__attribute__((interrupt)) void DoubleFault_Handler(interrupt_frame* frame){
    Panic("Double Fault Detected");
    while(true);
}

__attribute__((interrupt)) void GPFault_Handler(interrupt_frame* frame){
    Panic("General Protection Fault Detected");
    while(true);
}

__attribute__((interrupt)) void DivideByZeroFault_Handler(interrupt_frame* frame){
    Panic("Divide By Zero Detected");
    while(true);
}
__attribute__((interrupt)) void BoundRangeExceededFault_Handler(interrupt_frame* frame){
    Panic("Bound Range Exceeded Detected");
    while(true);

}
__attribute__((interrupt)) void InvalidOpcodeFault__Handler(interrupt_frame* frame){
    Panic("Invalid Opcode Detected");
    while(true);

}
__attribute__((interrupt)) void DeviceNotAvailableFault__Handler(interrupt_frame* frame){
    Panic("Device Not Available Detected");
    while(true);

}
__attribute__((interrupt)) void InvlalidTSSFault_Handler(interrupt_frame* frame){
    Panic("Invalid TSS Detected");
    while(true);

}
__attribute__((interrupt)) void SegmentNotPresentFault_Handler(interrupt_frame* frame){
    Panic("Segment Not Yet Present Detected");
    while(true);

}
__attribute__((interrupt)) void StackSegmentFault_Handler(interrupt_frame* frame){

    Panic("Stack Segmenent Fault Detected");
    while(true);
}
__attribute__((interrupt)) void FloatingPointExceptionFault_Handler(interrupt_frame* frame){
    Panic("Floating Point Exception Detected");
    while(true);

}
__attribute__((interrupt)) void AlignmentCheckFault_Handler(interrupt_frame* frame){
    Panic("Alighnment Check Fault Detected");
    while(true);

}
__attribute__((interrupt)) void SIMDFloatingPointExceptionFault_Handler(interrupt_frame* frame){
    Panic("SIMD Floating Point Exceptiont Detected");
    while(true);

}
__attribute__((interrupt)) void MachineCheckFault_Handler(interrupt_frame* frame)
{
    Panic("Machince Check Fault Detected");
    while(true);

}
__attribute__((interrupt)) void VirtualisationExceptionFault_Handler(interrupt_frame* frame){
    Panic("Virtualisation Exception Detected");
    while(true);

}
__attribute__((interrupt)) void SecurityExceptionFault_Handler(interrupt_frame* frame){
    Panic("Security Exception Detected");
    while(true);

}

__attribute__((interrupt)) void KeyboardInt_Handler(interrupt_frame* frame){
    uint8_t scancode = inb(0x60);

    HandleKeyboard(scancode);

    PIC_EndMaster();
}

__attribute__((interrupt)) void MouseInt_Handler(interrupt_frame* frame){

    uint8_t mouseData = inb(0x60);

    HandlePS2Mouse(mouseData);

    PIC_EndSlave();
}

__attribute__((interrupt)) void PITInt_Handler(interrupt_frame* frame){
    PIT::Tick();
    PIC_EndMaster();
}

void PIC_EndMaster(){
    outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_EndSlave(){
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}
   

void RemapPIC(){
    uint8_t a1, a2; 

    a1 = inb(PIC1_DATA);
    io_wait();
    a2 = inb(PIC2_DATA);
    io_wait();

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, 0x20);
    io_wait();
    outb(PIC2_DATA, 0x28);
    io_wait();

    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1);
    io_wait();
    outb(PIC2_DATA, a2);

}