#include "BasicRenderer.h"

BasicRenderer* GlobalRenderer;

BasicRenderer::BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF1_Font = psf1_Font;
    doubleBuffer = (uint32_t*)malloc(TargetFramebuffer->BufferSize);
    memset32(doubleBuffer, 0, TargetFramebuffer->BufferSize / 4);
    defaultCanvases = new DefaultCanvases();
    defaultCanvases->textCanvas = createTextCanvas(0,psf1_Font);
    defaultCanvases->overlayCanvas = createOverlayCanvas(1);
    /*defaultCanvases->mouseCanvas = createMouseCanvas(65536);
    canvasList = new LinkedList<Canvas>();
    canvasList.addItem(defaultCanvases->textCanvas);
    canvasList.addItem(defaultCanvases->overlayCanvas);
    canvasList.addItem(defaultCanvases->mouseCanvas);*/
    redrawing = false;
}

BasicRenderer::~BasicRenderer()
{
    GlobalRenderer = NULL;
    free(doubleBuffer);
    free(defaultCanvases->textCanvas);
    free(defaultCanvases);
    free(canvasList);
}

void BasicRenderer::PaintScreen()
{//   if(redrawing) return;


    redrawing = true;
    memcpy64(doubleBuffer,defaultCanvases->textCanvas->GetCanvasInfo()->buffer, 
        defaultCanvases->textCanvas->GetCanvasInfo()->bufferSize / 8);
    if(overlayImage!=NULL)
    {
        memcpy64(defaultCanvases->overlayCanvas->GetCanvasInfo()->buffer, overlayImage, 
            (defaultCanvases->overlayCanvas->GetCanvasInfo()->width*180/2));
    }
    for(uint64_t i = 0; i < defaultCanvases->overlayCanvas->GetCanvasInfo()->bufferSize / 4; i++)
    {
        doubleBuffer[i] += defaultCanvases->overlayCanvas->GetCanvasInfo()->buffer[i];
    }
    memcpy64(TargetFramebuffer->BaseAddress,doubleBuffer, TargetFramebuffer->BufferSize / 8);
    redrawing = false;
}

void BasicRenderer::SetOverlayImage(uint32_t* image)
{
    uint32_t* processOverlayImage = (uint32_t*)malloc(TargetFramebuffer->PixelsPerScanLine*180*32);
    memset32(processOverlayImage, 0, TargetFramebuffer->PixelsPerScanLine*180);
    unsigned int width = 320;
    unsigned int height = 180;
    
    // covert to screen width (it's a 320x180 atm) and center it;

    
    for(unsigned int y = 0; y < height; y++)
    {
        for(unsigned int x = 0; x < width; x ++)      
        {
            processOverlayImage[
                (TargetFramebuffer->PixelsPerScanLine * y) + (x + ((TargetFramebuffer->PixelsPerScanLine-width)/2))
                ] =
            image[(y * width) + x];
        }
    }
    overlayImage = processOverlayImage;
}

Canvas* BasicRenderer::createDefaultCanvas(uint32_t z_order)
{
    return new Canvas(0,0,TargetFramebuffer->PixelsPerScanLine,TargetFramebuffer->Height,z_order,Canvas::OVERLAY_MODE::ADD);
}

TextCanvas* BasicRenderer::createTextCanvas(uint32_t z_order, PSF1_FONT* psf1_Font){
    return new TextCanvas(0,0,TargetFramebuffer->PixelsPerScanLine,TargetFramebuffer->Height,z_order,Canvas::OVERLAY_MODE::ADD, psf1_Font);
}
OverlayCanvas* BasicRenderer::createOverlayCanvas(uint32_t z_order){
    return new OverlayCanvas(0,0,TargetFramebuffer->PixelsPerScanLine,TargetFramebuffer->Height,z_order,Canvas::OVERLAY_MODE::ADD);
}
MouseCanvas* BasicRenderer::createMouseCanvas(uint32_t z_order)
{
    return new MouseCanvas(0,0,TargetFramebuffer->PixelsPerScanLine,TargetFramebuffer->Height,z_order,Canvas::OVERLAY_MODE::ADD);
}

void BasicRenderer::registerCanvas(Canvas *canvas)
{
    canvasList->addItem(canvas);
}

void BasicRenderer::unregisterCanvas(Canvas *canvas)
{
    canvasList->removeItem(canvas);
}