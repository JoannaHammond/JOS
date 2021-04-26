#pragma once
#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline") //Optimization flags
#pragma GCC target("avx")  //Enable AVX

#include "Canvas.h"
#include "../utils/math/math.h"


namespace CanvasUtils {
    
    void* OR_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
        uint32_t maxScreenWidthToUse = min(dest->width - src->xorigin, src->width);
        uint32_t maxScreenHeigthToUse = min(dest->height - src->yorigin,src->height);
        for(uint32_t x = 0; x < maxScreenWidthToUse; x++)
            for(uint32_t y = 0; y < maxScreenHeigthToUse ; y++)
            {
                uint32_t destBufferOffset = x + src->xorigin + ((y + src->yorigin)*dest->width);
                uint32_t srcBufferOffset = x + (y*src->width);
                dest->buffer[destBufferOffset] |= src->buffer[srcBufferOffset];
            }

        return dest->buffer;
    }
    void* AND_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
        uint32_t maxScreenWidthToUse = min(dest->width - src->xorigin, src->width);
        uint32_t maxScreenHeigthToUse = min(dest->height - src->yorigin,src->height);
        for(uint32_t x = 0; x < maxScreenWidthToUse; x++)
            for(uint32_t y = 0; y < maxScreenHeigthToUse ; y++)
            {
                uint32_t destBufferOffset = x + src->xorigin + ((y + src->yorigin)*dest->width);
                uint32_t srcBufferOffset = x + (y*src->width);
                dest->buffer[destBufferOffset] &= src->buffer[srcBufferOffset];
            }

        return dest->buffer;
    }
    void* ADD_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
        uint32_t maxScreenWidthToUse = min(dest->width - src->xorigin, src->width);
        uint32_t maxScreenHeigthToUse = min(dest->height - src->yorigin,src->height);
        for(uint32_t x = 0; x < maxScreenWidthToUse; x++)
            for(uint32_t y = 0; y < maxScreenHeigthToUse ; y++)
            {
                uint32_t destBufferOffset = x + src->xorigin + ((y + src->yorigin)*dest->width);
                uint32_t srcBufferOffset = x + (y*src->width);
                dest->buffer[destBufferOffset] += src->buffer[srcBufferOffset];
            }

        return dest->buffer;
    }
    void* SUB_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
        uint32_t maxScreenWidthToUse = min(dest->width - src->xorigin, src->width);
        uint32_t maxScreenHeigthToUse = min(dest->height - src->yorigin,src->height);
        for(uint32_t x = 0; x < maxScreenWidthToUse; x++)
            for(uint32_t y = 0; y < maxScreenHeigthToUse ; y++)
            {
                uint32_t destBufferOffset = x + src->xorigin + ((y + src->yorigin)*dest->width);
                uint32_t srcBufferOffset = x + (y*src->width);
                dest->buffer[destBufferOffset] -= src->buffer[srcBufferOffset];
            }

        return dest->buffer;
    }
    void* MUL_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
        uint32_t maxScreenWidthToUse = min(dest->width - src->xorigin, src->width);
        uint32_t maxScreenHeigthToUse = min(dest->height - src->yorigin,src->height);
        for(uint32_t x = 0; x < maxScreenWidthToUse; x++)
            for(uint32_t y = 0; y < maxScreenHeigthToUse ; y++)
            {
                uint32_t destBufferOffset = x + src->xorigin + ((y + src->yorigin)*dest->width);
                uint32_t srcBufferOffset = x + (y*src->width);
                dest->buffer[destBufferOffset] *= src->buffer[srcBufferOffset];
            }
        return dest->buffer;
    }
    void* DIV_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
        uint32_t maxScreenWidthToUse = min(dest->width - src->xorigin, src->width);
        uint32_t maxScreenHeigthToUse = min(dest->height - src->yorigin,src->height);
        for(uint32_t x = 0; x < maxScreenWidthToUse; x++)
            for(uint32_t y = 0; y < maxScreenHeigthToUse ; y++)
            {
                uint32_t destBufferOffset = x + src->xorigin + ((y + src->yorigin)*dest->width);
                uint32_t srcBufferOffset = x + (y*src->width);
                dest->buffer[destBufferOffset] /= src->buffer[srcBufferOffset];
            }

        return dest->buffer;
    }
    void* COPY_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
        // NEEDS FIXING
         memcpy32(dest->buffer,src->buffer, src->pixelBufferSize);
         return dest->buffer;
    }
};