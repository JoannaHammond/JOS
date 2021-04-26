#include "pit.h"
#include "../../io/IO.h"
#include "../../rendering/BasicRenderer.h"

namespace PIT{
    bool paintRunning = false;
    double TimeSinceBoot = 0;
    double LastRefresh = 0;

    uint16_t Divisor = 8192;

    void Sleepd(double seconds){
        double startTime = TimeSinceBoot;
        while (TimeSinceBoot < startTime + seconds){
            asm("hlt");
        }
    }

    void Sleep(uint64_t milliseconds){
        Sleepd((double)milliseconds / 1000);
    }

    void SetDivisor(uint16_t divisor){
        if (divisor < 100) divisor = 100;
        Divisor = divisor;
        outb(0x40, (uint8_t)(divisor & 0x00ff));
        io_wait();
        outb(0x40, (uint8_t)((divisor & 0xff00) >> 8));
    }

    uint64_t GetFrequency(){
        return BaseFrequency / Divisor;
    }

    void SetFrequency(uint64_t frequency){
        SetDivisor(BaseFrequency / frequency);
    }

    void Tick(){
        TimeSinceBoot += 1 / (double)GetFrequency();

        
        // Every 32ms update screen (30fps)
        if(LastRefresh + 0.01666666 < TimeSinceBoot)
        {
            LastRefresh = TimeSinceBoot;
            if(GlobalRenderer != NULL && !paintRunning)
            {
                paintRunning = true;
                GlobalRenderer->PaintScreen();
                paintRunning = false;
            }
        }
    }
}