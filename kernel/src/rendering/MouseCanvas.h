#pragma once
#include "Canvas.h"
#include "../math.h"

class MouseCanvas : public Canvas {
    public:
    MouseCanvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, Canvas::OVERLAY_MODE mode);

    void DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t colour);
    void ClearMouseCursor(uint8_t* mouseCursor, Point position);

    void* Paint() override;

    private:
    uint32_t MouseCursorBuffer[16 * 16];
    uint32_t MouseCursorBufferAfter[16 * 16];
    bool MouseDrawn = false;
};