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
#include "../memory.h"
#include "../memory/heap.h"

class BasicRenderer{
    public:
    struct DefaultCanvases {
        TextCanvas *textCanvas;
        OverlayCanvas *overlayCanvas;
       // MouseCanvas *mouseCanvas;
    };

    DefaultCanvases* defaultCanvases;

    BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    ~BasicRenderer();
    void PaintScreen();
    void SetOverlayImage(uint32_t* image);

    Canvas* createDefaultCanvas(uint32_t z_order);
    TextCanvas* createTextCanvas(uint32_t z_order, PSF1_FONT* psf1_Font);
    OverlayCanvas* createOverlayCanvas(uint32_t z_order);
    MouseCanvas* createMouseCanvas(uint32_t z_order);
    void registerCanvas(Canvas *canvas);
    void unregisterCanvas(Canvas *canvas);

    private:
    Framebuffer* TargetFramebuffer;
    uint32_t* overlayImage = NULL;
    PSF1_FONT* PSF1_Font;
    uint32_t* doubleBuffer = NULL;
    bool redrawing = false;

    LinkedList<Canvas> *canvasList;
};

extern BasicRenderer* GlobalRenderer;