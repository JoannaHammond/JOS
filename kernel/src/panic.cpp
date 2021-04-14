#include "panic.h"
#include "BasicRenderer.h"

void Panic(const char* panicMessage){
    GlobalRenderer->ClearColour = 0x000000ff;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Kernel Panic");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);
}