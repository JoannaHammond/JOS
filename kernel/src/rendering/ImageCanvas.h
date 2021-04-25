#pragma once


#include "Canvas.h"
#include "../utils/math/math.h"

class ImageCanvas : public Canvas {
    public:
    ImageCanvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, Canvas::OVERLAY_MODE mode); 
    ~ImageCanvas();

    void SetImage(uint32_t* image);
    void* Paint() override;
};