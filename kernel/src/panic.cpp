#include "panic.h"
#include "utils/print.h"

void Panic(const char* panicMessage){

    __asm__ ("sti");

    while(1)    {
    GlobalPrinter.setClearColour(0x000000ff);
    GlobalPrinter.Clear();

    GlobalPrinter.SetCursorPosition(0, 0);

    GlobalPrinter.SetColor(0xffffffff);

    GlobalPrinter.Println("Kernel Panic");
    GlobalPrinter.Println("");
    GlobalPrinter.Println(panicMessage);

    for(unsigned long i = 0; i < 500000000; i++);

    GlobalPrinter.setClearColour(0x00ff0000);
    GlobalPrinter.Clear();

    GlobalPrinter.SetCursorPosition(0, 0);
    GlobalPrinter.SetColor(0xffffffff);

    GlobalPrinter.Println("Kernel Panic");
    GlobalPrinter.Println("");
    GlobalPrinter.Println(panicMessage);

    for(unsigned long i = 0; i < 500000000; i++);
    }
}