#include "SimpleDrawingCanvas.h"

SimpleDrawingCanvas::SimpleDrawingCanvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, 
    uint32_t height, uint32_t z_order, Canvas::OVERLAY_MODE mode) 
    : Canvas::Canvas(xorigin, yorigin, width, height, z_order, mode)
{
    
}

SimpleDrawingCanvas::~SimpleDrawingCanvas()
{

}

void* SimpleDrawingCanvas::Paint()
{
    dirty = false;
    return _canvasInfo.buffer;
}
