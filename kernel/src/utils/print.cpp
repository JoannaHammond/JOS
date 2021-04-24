#include "print.h"
Print GlobalPrinter;
    void Print::PrintText(const char* str)
    {
        if(textCanvas == NULL) return;
        textCanvas->Print(str);
    }
    void Print::Println(const char* str)
    {
        if(textCanvas == NULL) return;
        textCanvas->Println(str);
    }
    void Print::PrintChr(char chr)
    {
        if(textCanvas == NULL) return;
        textCanvas->PutChar(chr);
    }
    void Print::RegisterTextCanvas(TextCanvas* canvas)
    {
        textCanvas = canvas;
    }

    void Print::SetCursorPosition(uint64_t x, uint64_t y)
{
    textCanvas->SetCursorPosition(x,y);
}

    void Print::SetColor(uint32_t color)
    {
        textCanvas->Colour = color;
    }
    void Print::setClearColour(uint32_t clearColor){
        textCanvas->ClearColour = clearColor;
    }

    void Print::Clear()
    {
        textCanvas->Clear();
    }
