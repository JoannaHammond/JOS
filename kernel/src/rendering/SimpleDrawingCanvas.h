#pragma once


#include "Canvas.h"
#include "../utils/math/math.h"

class SimpleDrawingCanvas : public Canvas {
    public:
    SimpleDrawingCanvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, Canvas::OVERLAY_MODE mode); 
    ~SimpleDrawingCanvas();

    void* Paint() override;
};