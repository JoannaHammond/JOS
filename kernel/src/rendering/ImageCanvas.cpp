#include "ImageCanvas.h"

ImageCanvas::ImageCanvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, 
    uint32_t height, uint32_t z_order, Canvas::OVERLAY_MODE mode) 
    : Canvas::Canvas(xorigin, yorigin, width, height, z_order, mode)
{
    
}

ImageCanvas::~ImageCanvas()
{

}

void ImageCanvas::SetImage(uint32_t* image)
{
    Clear();
    memcpy32(_canvasInfo.buffer, image, _canvasInfo.width * _canvasInfo.height);
    dirty = true;
}

void* ImageCanvas::Paint()
{
    dirty = false;
    return _canvasInfo.buffer;
}
