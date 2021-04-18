#pragma once
#include "../rendering/BasicRenderer.h"
#include "../userinput/mouse.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

// Fault IRQs
#define IRQ_DIVIDE_BY_ZERO 0
#define IRQ_BOUND_RANGE_EXCEEDED 5
#define IRQ_INVALID_OPCODE 6
#define IRQ_DEVICE_NOT_AVAILABLE 7
#define IRQ_DOUBLE_FAULT 8
#define IRQ_INVALID_TSS 10
#define IRQ_SEGMENT_NOT_PRESENT 11
#define IRQ_STACK_SEGMENT_FAULT 12
#define IRQ_GENERAL_PROTECTION_FAULT 13
#define IRQ_PAGE_FAULT 14
#define IRQ_FLOATING_POINT_EXCEPTION 16
#define IRQ_ALIGNMENT_CHECK 17
#define IRQ_MACHINE_CHECK 18
#define IRQ_SIMD_FLOATING_POINT_EXCEPTION 19
#define IRQ_VIRTUALISATION_EXCEPTION 20
#define IRQ_SECURITY_EXCEPTION 30


struct interrupt_frame;
// Faults
__attribute__((interrupt)) void DivideByZeroFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void BoundRangeExceededFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void InvalidOpcodeFault__Handler(interrupt_frame* frame);
__attribute__((interrupt)) void DeviceNotAvailableFault__Handler(interrupt_frame* frame);
__attribute__((interrupt)) void InvlalidTSSFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void SegmentNotPresentFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void StackSegmentFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void FloatingPointExceptionFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void AlignmentCheckFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void SIMDFloatingPointExceptionFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void MachineCheckFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void VirtualisationExceptionFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void SecurityExceptionFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void PageFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void DoubleFault_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void GPFault_Handler(interrupt_frame* frame);

//Other Handlers
__attribute__((interrupt)) void KeyboardInt_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void MouseInt_Handler(interrupt_frame* frame);
__attribute__((interrupt)) void PITInt_Handler(interrupt_frame* frame);

void RemapPIC();
void PIC_EndMaster();
void PIC_EndSlave();