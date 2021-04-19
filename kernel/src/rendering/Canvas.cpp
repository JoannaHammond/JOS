#include "Canvas.h"

Canvas::Canvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, OVERLAY_MODE mode)
{
    _canvasInfo = new CanvasInfo();
    _canvasInfo->xorigin = xorigin;
    _canvasInfo->yorigin = yorigin;
    _canvasInfo->width = width;
    _canvasInfo->height = height;
    _canvasInfo->z_order = z_order;
    _canvasInfo->mode = mode;
    _canvasInfo->bufferSize = width * height * 4;
    _canvasInfo->buffer = (uint32_t*)malloc(_canvasInfo->bufferSize);
    memset32(_canvasInfo->buffer, 0, _canvasInfo->bufferSize / 4);
    dirty = true;
}

void Canvas::Clear(){
    memset32(_canvasInfo->buffer, ClearColour, _canvasInfo->bufferSize / 4);
    dirty = true;
}

void Canvas::Clear(size_t lines){
    memset32(_canvasInfo->buffer, ClearColour, _canvasInfo->width * lines);
    dirty = true;
}

void Canvas::PutPix(uint32_t x, uint32_t y, uint32_t colour){
    *(uint32_t*)(_canvasInfo->buffer + (x) + (y * _canvasInfo->width)) = colour;
    dirty = true;
}

uint32_t Canvas::GetPix(uint32_t x, uint32_t y){
    return *(uint32_t*)(_canvasInfo->buffer + (x) + (y * _canvasInfo->width ));
}

void Canvas::SetDirty()
{
    dirty = true;
}

void Canvas::ClearDirty()
{
    dirty = false;
}

Canvas::CanvasInfo* Canvas::GetCanvasInfo()
{
    return _canvasInfo;
}
