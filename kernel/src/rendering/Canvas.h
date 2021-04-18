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

    explicit Canvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, OVERLAY_MODE mode);

    private:
    CanvasInfo _canvasInfo;
};