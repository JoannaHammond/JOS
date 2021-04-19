#pragma once
#include <stddef.h>
#include <stdint.h>
#include "../memory/heap.h"
#include "../memory.h"

class Canvas {

    public:
    enum OVERLAY_MODE {
        OR,
        AND,
        ADD,
        MULT,
        SUB,
        DIV
    };

    struct CanvasInfo {
        uint32_t xorigin;
        uint32_t yorigin;
        uint32_t width;
        uint32_t height;
        uint32_t* buffer;
        uint64_t bufferSize;
        uint32_t z_order;
        OVERLAY_MODE mode;
    };

    Canvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, OVERLAY_MODE mode);

    void Clear();
    void Clear(size_t lines);

    void PutPix(uint32_t x, uint32_t y, uint32_t colour);
    uint32_t GetPix(uint32_t x, uint32_t y);

    void SetDirty();
    void ClearDirty();

    Canvas::CanvasInfo* GetCanvasInfo();

    unsigned int Colour = 0xffffffff;
    unsigned int ClearColour = 0;

    protected:
    CanvasInfo* _canvasInfo;
    bool dirty = true;
};