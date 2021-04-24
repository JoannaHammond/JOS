#include "LogoCanvas.h"

LogoCanvas::LogoCanvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, 
    uint32_t height, uint32_t z_order, Canvas::OVERLAY_MODE mode) 
    : Canvas::Canvas(xorigin, yorigin, width, height, z_order, mode)
{
    
}

LogoCanvas::~LogoCanvas()
{
    free(overlayImage);
}

void LogoCanvas::SetOverlayImage(uint32_t* image)
{
    uint32_t* processOverlayImage = (uint32_t*)malloc(_canvasInfo.width*180*32);
    memset32(processOverlayImage, 0, _canvasInfo.width*180);
    unsigned int width = 320;
    unsigned int height = 180;
    
    // covert to screen width (it's a 320x180 atm) and center it;
    
    for(unsigned int y = 0; y < height; y++)
    {
        for(unsigned int x = 0; x < width; x ++)      
        {
            processOverlayImage[
                (_canvasInfo.width * y) + (x + ((_canvasInfo.width-width)/2))
                ] =
            image[(y * width) + x];
        }
    }
    overlayImage = processOverlayImage;

    Clear();

    // Copy logo onto buffer (FOR NOW)
    memcpy32(_canvasInfo.buffer, overlayImage, _canvasInfo.width * 180);
}

void* LogoCanvas::Paint()
{
    dirty = false;
    return _canvasInfo.buffer;
}
