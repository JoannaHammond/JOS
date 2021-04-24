#include "BasicRenderer.h"

BasicRenderer* GlobalRenderer;

BasicRenderer::BasicRenderer(Framebuffer* targetFramebuffer)
{
    TargetFramebuffer = targetFramebuffer;
    rootCanvas = createDefaultCanvas(0);
    rootCanvas->Clear();
    redrawing = false;
}

BasicRenderer::~BasicRenderer()
{
    GlobalRenderer = NULL;
}

void BasicRenderer::PaintScreen()
{  
    if(rootCanvas == NULL || redrawing || !rootCanvas->IsDirty()) return;

    redrawing = true;
    void *paintBuffer = rootCanvas->Paint();
    memcpy32(TargetFramebuffer->BaseAddress,paintBuffer, TargetFramebuffer->BufferSize / 4);
    redrawing = false;
}

Canvas* BasicRenderer::createDefaultCanvas(uint32_t z_order)
{
    return new Canvas(0,0,TargetFramebuffer->PixelsPerScanLine,TargetFramebuffer->Height,z_order,Canvas::OVERLAY_MODE::COPY);
}

TextCanvas* BasicRenderer::createTextCanvas(uint32_t z_order, PSF1_FONT* psf1_Font){
    return new TextCanvas(0,0,TargetFramebuffer->PixelsPerScanLine,TargetFramebuffer->Height,z_order,Canvas::OVERLAY_MODE::COPY, psf1_Font);
}
MouseCanvas* BasicRenderer::createMouseCanvas(uint32_t z_order)
{
    return new MouseCanvas(0,0,TargetFramebuffer->PixelsPerScanLine,TargetFramebuffer->Height,z_order,Canvas::OVERLAY_MODE::ADD);
}

Canvas* BasicRenderer::getRootCanvas() {
    return rootCanvas;
}