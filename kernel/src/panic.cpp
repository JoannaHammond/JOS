#include "panic.h"
#include "BasicRenderer.h"

void Panic(const char* panicMessage){

    __asm__ ("sti");

    while(1)    {
    GlobalRenderer->ClearColour = 0x000000ff;
    GlobalRenderer->Clear(48);

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Kernel Panic");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);

    for(unsigned long i = 0; i < 500000000; i++);

    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear(48);

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Kernel Panic");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);
    for(unsigned long i = 0; i < 500000000; i++);
    }
}