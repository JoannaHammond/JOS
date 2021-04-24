#pragma once

#include "Canvas.h"
#include "../math.h"

class LogoCanvas : public Canvas {
    public:
    LogoCanvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, Canvas::OVERLAY_MODE mode); 
    ~LogoCanvas();

    void SetOverlayImage(uint32_t* image);
    void* Paint() override;

    private:
    uint32_t* overlayImage = NULL;
};