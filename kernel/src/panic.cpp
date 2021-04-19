#include "panic.h"
#include "rendering/BasicRenderer.h"

void Panic(const char* panicMessage){

    __asm__ ("sti");

    //while(1)    {
    //GlobalRenderer->defaultCanvases->textCanvas->ClearColour = 0x000000ff;
    //GlobalRenderer->defaultCanvases->textCanvas->Clear();

    GlobalRenderer->defaultCanvases->textCanvas->CursorPosition = {0, 0};

    GlobalRenderer->defaultCanvases->textCanvas->Colour = 0xffffffff;

    GlobalRenderer->defaultCanvases->textCanvas->Print("Kernel Panic");

    GlobalRenderer->defaultCanvases->textCanvas->Next();
    GlobalRenderer->defaultCanvases->textCanvas->Next();

    GlobalRenderer->defaultCanvases->textCanvas->Print(panicMessage);

    /*for(unsigned long i = 0; i < 500000000; i++);

    GlobalRenderer->defaultCanvases->textCanvas->ClearColour = 0x00ff0000;
    GlobalRenderer->defaultCanvases->textCanvas->Clear();

    GlobalRenderer->defaultCanvases->textCanvas->CursorPosition = {0, 0};

    GlobalRenderer->defaultCanvases->textCanvas->Colour = 0xffffffff;

    GlobalRenderer->defaultCanvases->textCanvas->Print("Kernel Panic");

    GlobalRenderer->defaultCanvases->textCanvas->Next();
    GlobalRenderer->defaultCanvases->textCanvas->Next();

    GlobalRenderer->defaultCanvases->textCanvas->Print(panicMessage);
    for(unsigned long i = 0; i < 500000000; i++);
    }*/
}