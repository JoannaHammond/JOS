#include "MouseCanvas.h"


MouseCanvas::MouseCanvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, Canvas::OVERLAY_MODE mode) : 
    Canvas(xorigin, yorigin, width, height, z_order, mode) {

    }

void MouseCanvas::ClearMouseCursor(uint8_t* mouseCursor, Point position){
    if (!MouseDrawn) return;

    int xMax = 16;
    int yMax = 16;
    int differenceX = _canvasInfo->width - position.X;
    int differenceY = _canvasInfo->height - position.Y;

    if (differenceX < 16) xMax = differenceX;
    if (differenceY < 16) yMax = differenceY;

    for (int y = 0; y < yMax; y++){
        for (int x = 0; x < xMax; x++){
            int bit = y * 16 + x;
            int byte = bit / 8;
            if ((mouseCursor[byte] & (0b10000000 >> (x % 8))))
            {
                if (GetPix(position.X + x, position.Y + y) == MouseCursorBufferAfter[x + y *16]){
                    PutPix(position.X + x, position.Y + y, MouseCursorBuffer[x + y * 16]);
                }
            }
        }
    }
}

void MouseCanvas::DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t colour){


    int xMax = 16;
    int yMax = 16;
    int differenceX = _canvasInfo->width - position.X;
    int differenceY = _canvasInfo->height - position.Y;

    if (differenceX < 16) xMax = differenceX;
    if (differenceY < 16) yMax = differenceY;

    for (int y = 0; y < yMax; y++){
        for (int x = 0; x < xMax; x++){
            int bit = y * 16 + x;
            int byte = bit / 8;
            if ((mouseCursor[byte] & (0b10000000 >> (x % 8))))
            {
                MouseCursorBuffer[x + y * 16] = GetPix(position.X + x, position.Y + y);
                PutPix(position.X + x, position.Y + y, colour);
                MouseCursorBufferAfter[x + y * 16] = GetPix(position.X + x, position.Y + y);

            }
        }
    }

    MouseDrawn = true;
}