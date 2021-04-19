#pragma once

#include "Canvas.h"
#include "../math.h"
#include "../simpleFonts.h" 

class TextCanvas : public Canvas {
    public:
    TextCanvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, Canvas::OVERLAY_MODE mode, PSF1_FONT *font); 
        

    void Clear();
    void ResetCursor();
    void ClearChar();
    void Next();
    void Print(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void PutChar(char chr);
    void Println(const char* str);
    void ScrollScreenUpLn();
    void CheckScreenOverFlow();
    Point CursorPosition;

    private:
    PSF1_FONT* psf1_Font;
};