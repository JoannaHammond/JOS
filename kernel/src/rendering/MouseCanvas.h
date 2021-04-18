#pragma once
#include "Canvas.h"

class MouseCanvas : public Canvas {
    public:
    MouseCanvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, Canvas::OVERLAY_MODE mode) : 
    Canvas(xorigin, yorigin, width, height, z_order, mode) {}
};