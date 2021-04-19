#pragma once

#include "Canvas.h"

class OverlayCanvas : public Canvas {
    public:
    OverlayCanvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, Canvas::OVERLAY_MODE mode);

};