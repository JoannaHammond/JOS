#pragma once
#include "../rendering/TextCanvas.h"


class Print {
    public:
    void PrintText(const char* str);
    void Println(const char* str);
    void PrintChr(char chr);
    void RegisterTextCanvas(TextCanvas* canvas);
    void SetCursorPosition(uint64_t x, uint64_t y);
    void SetColor(uint32_t color);
    void setClearColour(uint32_t clearColour);
    void Clear();

    private:
    TextCanvas* textCanvas;

};

extern Print GlobalPrinter;
