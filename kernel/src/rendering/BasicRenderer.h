#pragma once
#include "../math.h"
#include "Framebuffer.h"
#include "../simpleFonts.h" 
#include <stdint.h>
#include "Canvas.h"
#include "TextCanvas.h"
#include "OverlayCanvas.h"
#include "MouseCanvas.h"
#include "../utils/lists/LinkedList.h"

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
    void SetOverlayImage(uint32_t* image);

    Canvas* createDefaultCanvas(uint32_t z_order);
    TextCanvas* createTextCanvas(uint32_t z_order);
    OverlayCanvas* createOverlayCanvas(uint32_t z_order);
    MouseCanvas* createMouseCanvas(uint32_t z_order);
    void registerCanvas(Canvas *canvas);
    void unregisterCanvas(Canvas *canvas);

    private:
    uint32_t* overlayImage = NULL;
    PSF1_FONT* PSF1_Font;
    bool MouseDrawn;
    uint32_t* doubleBuffer = NULL;
    uint32_t* consoleBuffer = NULL;
    uint32_t* overlayBuffer = NULL;
    bool dirty = true;
    bool redrawing = false;

    LinkedList<Canvas>* canvasList;
};

extern BasicRenderer* GlobalRenderer;