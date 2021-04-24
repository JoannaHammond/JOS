#pragma once
#include <stddef.h>
#include <stdint.h>
#include "../memory/heap.h"
#include "../memory.h"
#include "../utils/lists/LinkedList.hpp"

class Canvas {

    public:
    enum OVERLAY_MODE {
        OR,
        AND,
        ADD,
        MUL,
        SUB,
        DIV,
        COPY
    };

    struct CanvasInfo {
        uint32_t xorigin;
        uint32_t yorigin;
        uint32_t width;
        uint32_t height;
        uint32_t* buffer;
        uint64_t bufferSize;
        uint64_t pixelBufferSize;
        uint32_t z_order;
        OVERLAY_MODE mode;
    };

    Canvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, OVERLAY_MODE mode);
    ~Canvas();
    
    virtual void Clear();
    virtual void Clear(size_t lines);

    virtual void PutPix(uint32_t x, uint32_t y, uint32_t colour);
    virtual uint32_t GetPix(uint32_t x, uint32_t y);

    virtual void* Paint();

    virtual void AddChildCanvas(Canvas* c);
    virtual void RemoveChildCanvas(Canvas* c);

    virtual void SetDirty();
    virtual void ClearDirty();
    virtual bool IsDirty();

    Canvas::CanvasInfo* GetCanvasInfo();

    unsigned int Colour = 0xffffffff;
    unsigned int ClearColour = 0;

    protected:
    CanvasInfo _canvasInfo;
    bool dirty = true;

    private:
    LinkedList<Canvas> childCanvases;
    
    // testing crap
    Canvas* test = NULL;
    int32_t t = 0;

};