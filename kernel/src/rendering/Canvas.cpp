#include "Canvas.h"
#include "CanvasUtils.hpp"
#include "../utils/print.h"
#include "../utils/cstr.h"

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
    _canvasInfo.buffer = (uint32_t *)malloc(_canvasInfo.bufferSize);
    memset32(_canvasInfo.buffer, 0, _canvasInfo.pixelBufferSize);

    dirty = true;
}

Canvas::~Canvas()
{
    free(_canvasInfo.buffer);
}

void Canvas::Clear()
{
    memset32(_canvasInfo.buffer, ClearColour, _canvasInfo.bufferSize / 4);
    dirty = true;
}

void Canvas::Clear(size_t lines)
{
    memset32(_canvasInfo.buffer, ClearColour, _canvasInfo.width * lines);
    dirty = true;
}

void Canvas::PutPix(uint32_t x, uint32_t y, uint32_t colour)
{
    *(uint32_t *)(_canvasInfo.buffer + (x) + (y * _canvasInfo.width)) = colour;
    dirty = true;
}

uint32_t Canvas::GetPix(uint32_t x, uint32_t y)
{
    return *(uint32_t *)(_canvasInfo.buffer + (x) + (y * _canvasInfo.width));
}

void Canvas::SetDirty()
{
    dirty = true;
}

void Canvas::ClearDirty()
{
    dirty = false;
}

Canvas::CanvasInfo *Canvas::GetCanvasInfo()
{
    return &_canvasInfo;
}

void *Canvas::Paint()
{
    if (!IsDirty())
        return _canvasInfo.buffer;
    for (Canvas *c = childCanvases.firstItem(); c != NULL; c = childCanvases.nextItem())
    {
        c->Paint();
        // This will need to be a lot cleverer, we need overlays, subwindows, etc.
        //memcpy32(_canvasInfo.buffer,cBuffer, _canvasInfo.bufferSize / 4);
        switch (c->_canvasInfo.mode)
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

void Canvas::AddChildCanvas(Canvas *c)
{
    childCanvases.addItem(c);
}

void Canvas::RemoveChildCanvas(Canvas *c)
{
    childCanvases.removeItem(c);
}

bool Canvas::IsDirty()
{
    bool dirty = this->dirty;
    for (Canvas *c = childCanvases.firstItem(); c != NULL; c = childCanvases.nextItem())
    {
        dirty |= c->dirty;
    }
    return dirty;
}


void Canvas::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t colour)
{
    
    // Iterators, counters required by algorithm
    int32_t x, y, xe, ye;
    // Calculate line deltas
    double dx = ((int32_t)x2 - (int32_t)x1);
    double dy = ((int32_t)y2 - (int32_t)y1);   

    // Create a positive copy of deltas
    double dx1 = abs(dx);
    double dy1 = abs(dy);  

    // Calculate error intervals for both axis
    double errorMult = 2.0;
    double cpx = errorMult * (dy1 - dx1);
    double cpy = errorMult * (dx1 - dy1); 
    double px = cpx;
    double py = cpy; 

    // The line is X-axis dominant
    if (dy1 <= dx1)
    { 
        // Line is drawn left to right
        if (dx >= 0.0)
        {
            x = x1;
            y = y1;
            xe = x2;
        }
        else
        { 
            // Line is drawn right to left (swap ends)
            x = x2;
            y = y2;
            xe = x1;
        }
        // Draw first pixel
        if(x>=0 && y>=0 && x<=_canvasInfo.width && y<=_canvasInfo.height)
            _canvasInfo.buffer[(y * _canvasInfo.width) + x] = colour;         
        // Rasterize the line
        while(x < xe)
        {
            x++; 
            // Deal with octants...
            if (px < 0.0)
                px += errorMult * dy1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    y++;
                else
                    y--;
                px += cpx;
            } 
            if(x>=0 && y>=0 && x<=_canvasInfo.width && y<=_canvasInfo.height)
                _canvasInfo.buffer[(y * _canvasInfo.width) + x] = colour;         
            }
    }
    else    // The line is Y-axis dominant      
    { 
        // Line is drawn bottom to top
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        else
        { 
            // Line is drawn top to bottom
            x = x2;
            y = y2;
            ye = y1;
        }
        // Draw first pixel        
        if(x>=0 && y>=0 && x<=_canvasInfo.width && y<=_canvasInfo.height)
            _canvasInfo.buffer[(y * _canvasInfo.width) + x] = colour;         
        // Rasterize the line
        while(y < ye)
        {
            y++; 
            // Deal with octants...
            if (py <= 0)
                py += errorMult * dx1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    x++;
                else
                    x--;
                py += cpy;
            } 
            // Draw pixel from line span at currently rasterized position
            if(x>=0 && y>=0 && x<=_canvasInfo.width && y<=_canvasInfo.height)
                _canvasInfo.buffer[(y * _canvasInfo.width) + x] = colour;         
       }
    }
}

void Canvas::DrawTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, uint32_t colour)
{
    DrawLine(x1, y1, x2, y2, colour);
    DrawLine(x2, y2, x3, y3, colour);
    DrawLine(x3, y3, x1, y1, colour);
}