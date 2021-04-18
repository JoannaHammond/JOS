#include "Canvas.h"

Canvas::Canvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, OVERLAY_MODE mode)
{
    _canvasInfo.xorigin = xorigin;
    _canvasInfo.yorigin = yorigin;
    _canvasInfo.width = width;
    _canvasInfo.height = height;
    _canvasInfo.z_order = z_order;
    _canvasInfo.mode = mode;
    _canvasInfo.bufferSize = (width - xorigin) * (height - yorigin) * 32;
    _canvasInfo.buffer = (uint32_t*)malloc(_canvasInfo.bufferSize);
    memset32(_canvasInfo.buffer, 0, _canvasInfo.bufferSize / 4);
}