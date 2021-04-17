#pragma once
#include "math.h"
#include "Framebuffer.h"
#include "simpleFonts.h" 
#include <stdint.h>

class BasicRenderer{
    public:
    BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    ~BasicRenderer();
    Framebuffer* TargetFramebuffer;
    Point CursorPosition;
    uint32_t MouseCursorBuffer[16 * 16];
    uint32_t MouseCursorBufferAfter[16 * 16];
    unsigned int Colour;
    unsigned int ClearColour;
    void Print(const char* str);
    void Println(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void PutChar(char chr);
    void PutPix(uint32_t x, uint32_t y, uint32_t colour);
    uint32_t GetPix(uint32_t x, uint32_t y);
    void ClearChar();
    void Clear();
    void Clear(size_t lines);
    void Next();
    void DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t colour);
    void ClearMouseCursor(uint8_t* mouseCursor, Point position);
    void CheckScreenOverFlow();
    void ScrollScreenUpLn();
    void PaintScreen();

    private:

    PSF1_FONT* PSF1_Font;
    bool MouseDrawn;
    uint32_t* doubleBuffer = NULL;
    bool dirty = true;
    bool redrawing = false;
};

extern BasicRenderer* GlobalRenderer;