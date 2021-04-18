//#pragma GCC optimize("O3","unroll-loops","inline") //Optimization flags
//#pragma GCC option("arch=native","tune=native","no-zero-upper") //Enable AVX
//#pragma GCC target("avx")  //Enable AVX
#include "BasicRenderer.h"
#include "memory.h"
#include "memory/heap.h"
#include "paging/PageFrameAllocator.h"

BasicRenderer* GlobalRenderer;

BasicRenderer::BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF1_Font = psf1_Font;
    Colour = 0xffffffff;
    ClearColour = 0x00000000;
    CursorPosition = {0, 0};
    doubleBuffer = (uint32_t*)malloc(TargetFramebuffer->BufferSize);
    memset32(doubleBuffer, ClearColour, TargetFramebuffer->BufferSize / 4);
    consoleBuffer = (uint32_t*)malloc(TargetFramebuffer->BufferSize);
    memset32(consoleBuffer, ClearColour, TargetFramebuffer->BufferSize / 4);
    overlayBuffer = (uint32_t*)malloc(TargetFramebuffer->BufferSize);
    memset32(overlayBuffer, ClearColour, TargetFramebuffer->BufferSize / 4);
    dirty = true;
    redrawing = false;
}

BasicRenderer::~BasicRenderer()
{
    free(doubleBuffer);
    free(consoleBuffer);
    free(overlayBuffer);
    free(overlayImage);
}

void BasicRenderer::PutPix(uint32_t x, uint32_t y, uint32_t colour){
    *(uint32_t*)(overlayBuffer + (x) + (y * TargetFramebuffer->PixelsPerScanLine)) = colour;
    dirty = true;
}

uint32_t BasicRenderer::GetPix(uint32_t x, uint32_t y){
    return *(uint32_t*)(overlayBuffer + (x) + (y * TargetFramebuffer->PixelsPerScanLine ));
}

void BasicRenderer::ClearMouseCursor(uint8_t* mouseCursor, Point position){
    if (!MouseDrawn) return;

    int xMax = 16;
    int yMax = 16;
    int differenceX = TargetFramebuffer->Width - position.X;
    int differenceY = TargetFramebuffer->Height - position.Y;

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

void BasicRenderer::DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t colour){


    int xMax = 16;
    int yMax = 16;
    int differenceX = TargetFramebuffer->Width - position.X;
    int differenceY = TargetFramebuffer->Height - position.Y;

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

void BasicRenderer::Clear(){
    memset32(consoleBuffer, ClearColour, TargetFramebuffer->BufferSize / 4);
    CursorPosition = {0,0};
    dirty = true;
}

void BasicRenderer::Clear(size_t lines){
    memset32(consoleBuffer, ClearColour, TargetFramebuffer->PixelsPerScanLine * lines);
    CursorPosition = {0,0};
    dirty = true;
}


void BasicRenderer::ClearChar(){

    if (CursorPosition.X == 0){
        CursorPosition.X = TargetFramebuffer->Width;
        CursorPosition.Y -= 16;
        if (CursorPosition.Y < 0) CursorPosition.Y = 0;
    }

    unsigned int xOff = CursorPosition.X;
    unsigned int yOff = CursorPosition.Y;

    unsigned int* pixPtr = (unsigned int*)overlayBuffer;
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff - 8; x < xOff; x++){
                    *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = ClearColour;
        }
    }

    CursorPosition.X -= 8;

    if (CursorPosition.X < 0){
        CursorPosition.X = TargetFramebuffer->Width;
        CursorPosition.Y -= 16;
        if (CursorPosition.Y < 0) CursorPosition.Y = 0;
    }
    dirty = true;
}

void BasicRenderer::Next(){
    CursorPosition.X = 0;
    CursorPosition.Y += 16;
    CheckScreenOverFlow();
}

void BasicRenderer::Print(const char* str)
{
    
    char* chr = (char*)str;
    while(*chr != 0){
        PutChar(*chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X+=8;
        if(CursorPosition.X + 8 > TargetFramebuffer->Width)
        {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
            CheckScreenOverFlow();
        }
        chr++;
    }
}

void BasicRenderer::PutChar(char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int* pixPtr = (unsigned int*)consoleBuffer;
    char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = Colour;
                }

        }
        fontPtr++;
    }
    dirty = true;   
}

void BasicRenderer::PutChar(char chr)
{
    PutChar(chr, CursorPosition.X, CursorPosition.Y);
    CursorPosition.X += 8;
    if (CursorPosition.X + 8 > TargetFramebuffer->Width){
        CursorPosition.X = 0; 
        CursorPosition.Y += 16;
    }
    CheckScreenOverFlow();
}

void BasicRenderer::Println(const char* str){
    Print(str);
    Next();
}

void BasicRenderer::PaintScreen()
{   if(redrawing || !dirty) return;


    redrawing = true;
    memcpy64(doubleBuffer,consoleBuffer, (TargetFramebuffer->BufferSize / 8));
    if(overlayImage!=NULL)
    {
        memcpy64(overlayBuffer,overlayImage, (1080*180));
    }
    for(uint64_t i = 0; i < TargetFramebuffer->BufferSize / 4; i ++)
    {
        doubleBuffer[i] += overlayBuffer[i];
    }
    memcpy64(TargetFramebuffer->BaseAddress,doubleBuffer, (TargetFramebuffer->BufferSize / 8));
    dirty = false;
    redrawing = false;
}

void BasicRenderer::ScrollScreenUpLn()
{
    void* startline = consoleBuffer + (16 * TargetFramebuffer->PixelsPerScanLine);
    uint64_t count = (TargetFramebuffer->BufferSize/4) - (16*TargetFramebuffer->PixelsPerScanLine);
    void* clearLineAddress = consoleBuffer + (TargetFramebuffer->BufferSize/4) - (16 * TargetFramebuffer->PixelsPerScanLine);
    memcpy32(consoleBuffer, startline, count);
    memset32(clearLineAddress, ClearColour, (16 * TargetFramebuffer->PixelsPerScanLine));   
    dirty = true;
}

void BasicRenderer::CheckScreenOverFlow()
{
    if(CursorPosition.Y > TargetFramebuffer->Height - 16)
    {
        CursorPosition.Y -= 16;
        ScrollScreenUpLn();
    }
}

void BasicRenderer::SetOverlayImage(uint32_t* image)
{
    uint32_t* processOverlayImage = (uint32_t*)malloc(TargetFramebuffer->PixelsPerScanLine*180*32);
    memset32(processOverlayImage, 0, TargetFramebuffer->PixelsPerScanLine*180);

    // covert to screen width (it's a 320x180 atm) and center it;

    for(int i = 0; i < 320; i ++)
    {
        for(int j = 0; j < 180; j++)
        {
            processOverlayImage[
                (TargetFramebuffer->PixelsPerScanLine * j) + (i + ((TargetFramebuffer->PixelsPerScanLine-320)/2))
                ] =
            image[(j * 320) + i];
        }
    }
    overlayImage = processOverlayImage;
}