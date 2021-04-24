#pragma once

#include "Canvas.h"

namespace CanvasUtils {
    
    void* OR_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
        for(uint64_t i = 0; i < src->width * 180; i++)
        {
            dest->buffer[i] |= src->buffer[i];
        }

        return dest->buffer;
    }
    void* AND_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
        for(uint64_t i = 0; i < src->width * 180; i++)
        {
            dest->buffer[i] &= src->buffer[i];
        }

        return dest->buffer;
    }
    void* ADD_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){

        for(uint64_t i = 0; i < src->width * 180; i++)
        {
            dest->buffer[i] += src->buffer[i];
        }

        return dest->buffer;
    }
    void* SUB_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
        for(uint64_t i = 0; i < src->width * 180; i++)
        {
            dest->buffer[i] -= src->buffer[i];
        }

        return dest->buffer;
    }
    void* MUL_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
        for(uint64_t i = 0; i < src->width * 180; i++)
        {
            dest->buffer[i] *= src->buffer[i];
        }

        return dest->buffer;
    }
    void* DIV_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
        for(uint64_t i = 0; i < src->width * 180; i++)
        {
            dest->buffer[i] /= src->buffer[i];
        }

        return dest->buffer;
    }
    void* COPY_BLIT(Canvas::CanvasInfo* dest, Canvas::CanvasInfo* src){
         memcpy32(dest->buffer,src->buffer, src->pixelBufferSize);
         return dest->buffer;
    }

    
};