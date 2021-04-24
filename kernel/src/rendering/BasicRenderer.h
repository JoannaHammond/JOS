#pragma once
#include "../math.h"
#include "Framebuffer.h"
#include "../simpleFonts.h" 
#include <stdint.h>
#include "Canvas.h"
#include "TextCanvas.h"
#include "MouseCanvas.h"
#include "../memory.h"
#include "../memory/heap.h"

class BasicRenderer{
    public:

    BasicRenderer(Framebuffer* targetFramebuffer);
    ~BasicRenderer();
    void PaintScreen();
    void SetOverlayImage(uint32_t* image);
    Canvas* getRootCanvas();

    Canvas* createDefaultCanvas(uint32_t z_order);
    TextCanvas* createTextCanvas(uint32_t z_order, PSF1_FONT* psf1_Font);
    MouseCanvas* createMouseCanvas(uint32_t z_order);

    private:
    Framebuffer* TargetFramebuffer;
    uint32_t* overlayImage = NULL;
    bool redrawing = false;
    Canvas* rootCanvas;
};

extern BasicRenderer* GlobalRenderer;