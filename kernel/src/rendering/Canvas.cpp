#include "Canvas.h"
#include "CanvasUtils.hpp"

Canvas::Canvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, uint32_t height, uint32_t z_order, OVERLAY_MODE mode)
{
    _canvasInfo.xorigin = xorigin;
    _canvasInfo.yorigin = yorigin;
    _canvasInfo.width = width;
    _canvasInfo.height = height;
    _canvasInfo.z_order = z_order;
    _canvasInfo.mode = mode;
    _canvasInfo.pixelBufferSize = width * height;
    _canvasInfo.bufferSize = _canvasInfo.pixelBufferSize * 4;
    _canvasInfo.buffer = (uint32_t*)malloc(_canvasInfo.bufferSize);
    //memset32(_canvasInfo.buffer, 0, _canvasInfo.bufferSize / 4);
    test = NULL;
    t = 0;

    dirty = true;
}

Canvas::~Canvas()
{
    free(_canvasInfo.buffer);
}

void Canvas::Clear(){
    memset32(_canvasInfo.buffer, ClearColour, _canvasInfo.bufferSize / 4);
    dirty = true;
}

void Canvas::Clear(size_t lines){
    memset32(_canvasInfo.buffer, ClearColour, _canvasInfo.width * lines);
    dirty = true;
}

void Canvas::PutPix(uint32_t x, uint32_t y, uint32_t colour){
    *(uint32_t*)(_canvasInfo.buffer + (x) + (y * _canvasInfo.width)) = colour;
    dirty = true;
}

uint32_t Canvas::GetPix(uint32_t x, uint32_t y){
    return *(uint32_t*)(_canvasInfo.buffer + (x) + (y * _canvasInfo.width ));
}

void Canvas::SetDirty()
{
    dirty = true;
}

void Canvas::ClearDirty()
{
    dirty = false;
}

Canvas::CanvasInfo* Canvas::GetCanvasInfo()
{
    return &_canvasInfo;
}

void* Canvas::Paint()
{
    
    for(Canvas* c = childCanvases.firstItem(); c != NULL ; c = childCanvases.nextItem())
    {
        c->Paint();
        // This will need to be a lot cleverer, we need overlays, subwindows, etc.
        //memcpy32(_canvasInfo.buffer,cBuffer, _canvasInfo.bufferSize / 4);
        switch(c->_canvasInfo.mode)
        {
            case ADD:
                CanvasUtils::ADD_BLIT(&_canvasInfo, &c->_canvasInfo);
                break;
            case SUB:
                CanvasUtils::SUB_BLIT(&_canvasInfo, &c->_canvasInfo);
                break;
            case MUL:
                CanvasUtils::MUL_BLIT(&_canvasInfo, &c->_canvasInfo);
                break;
            case DIV:
                CanvasUtils::DIV_BLIT(&_canvasInfo, &c->_canvasInfo);
                break;
            case OR:
                CanvasUtils::OR_BLIT(&_canvasInfo, &c->_canvasInfo);
                break;
            case AND:
                CanvasUtils::AND_BLIT(&_canvasInfo, &c->_canvasInfo);
                break;
            case COPY:
                CanvasUtils::COPY_BLIT(&_canvasInfo, &c->_canvasInfo);
                break;
            default:
                CanvasUtils::ADD_BLIT(&_canvasInfo, &c->_canvasInfo);
                break;
        }
    }

    return _canvasInfo.buffer;
}



void Canvas::AddChildCanvas(Canvas* c)
{
    childCanvases.addItem(c);
}

void Canvas::RemoveChildCanvas(Canvas* c)
{
    childCanvases.removeItem(c);
}

bool Canvas::IsDirty() {
    return dirty;
}