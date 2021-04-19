#include "TextCanvas.h"

TextCanvas::TextCanvas(uint32_t xorigin, uint32_t yorigin, uint32_t width, 
    uint32_t height, uint32_t z_order, Canvas::OVERLAY_MODE mode, PSF1_FONT *font) 
    : Canvas::Canvas(xorigin, yorigin, width, height, z_order, mode)
{
    psf1_Font = font;
    CursorPosition = {0,0};
}


void TextCanvas::ClearChar(){

    if (CursorPosition.X == 0){
        CursorPosition.X = _canvasInfo->width;
        CursorPosition.Y -= 16;
        if (CursorPosition.Y < 0) CursorPosition.Y = 0;
    }

    unsigned int xOff = CursorPosition.X;
    unsigned int yOff = CursorPosition.Y;

    unsigned int* pixPtr = (unsigned int*)_canvasInfo->buffer;
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff - 8; x < xOff; x++){
                    *(unsigned int*)(pixPtr + x + (y * _canvasInfo->width)) = ClearColour;
        }
    }

    CursorPosition.X -= 8;

    if (CursorPosition.X < 0){
        CursorPosition.X = _canvasInfo->width;
        CursorPosition.Y -= 16;
        if (CursorPosition.Y < 0) CursorPosition.Y = 0;
    }
    dirty = true;
}

void TextCanvas::Next(){
    CursorPosition.X = 0;
    CursorPosition.Y += 16;
    CheckScreenOverFlow();
}

void TextCanvas::Print(const char* str)
{
    
    char* chr = (char*)str;
    while(*chr != 0){
        PutChar(*chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X+=8;
        if(CursorPosition.X + 8 > _canvasInfo->width)
        {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
            CheckScreenOverFlow();
        }
        chr++;
    }
}

void TextCanvas::PutChar(char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int* pixPtr = (unsigned int*)_canvasInfo->buffer;
    char* fontPtr = (char*)psf1_Font->glyphBuffer + (chr * psf1_Font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(unsigned int*)(pixPtr + x + (y * _canvasInfo->width)) = Colour;
                }

        }
        fontPtr++;
    }
    dirty = true;   
}

void TextCanvas::PutChar(char chr)
{
    PutChar(chr, CursorPosition.X, CursorPosition.Y);
    CursorPosition.X += 8;
    if (CursorPosition.X + 8 > _canvasInfo->width){
        CursorPosition.X = 0; 
        CursorPosition.Y += 16;
    }
    CheckScreenOverFlow();
}

void TextCanvas::Println(const char* str){
    Print(str);
    Next();
}

void TextCanvas::ScrollScreenUpLn()
{
    /*void* startline = _canvasInfo->buffer + (16 * _canvasInfo->width);
    uint64_t count = (_canvasInfo->bufferSize/4) - (16*_canvasInfo->width);
    void* clearLineAddress = _canvasInfo->buffer + (_canvasInfo->bufferSize/4) - (16 * _canvasInfo->width);
    memcpy32(_canvasInfo->buffer, startline, count);
    memset32(clearLineAddress, ClearColour, (16 * _canvasInfo->width));   
    dirty = true;*/
}

void TextCanvas::CheckScreenOverFlow()
{
    if(CursorPosition.Y > _canvasInfo->height - 16)
    {
        CursorPosition.Y -= 16;
        ScrollScreenUpLn();
    }
}

void TextCanvas::Clear()
{
    Canvas::Clear();
    ResetCursor();
}

void TextCanvas::ResetCursor()
{
    CursorPosition = {0,0};
}

