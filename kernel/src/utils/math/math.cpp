#include "math.h"

uint32_t min(uint32_t a, uint32_t b)
{
    if(a < b)
        return a;
    else   
        return b;
}

uint32_t abs(uint32_t a)
{
    if(a>0)
        return a;
    else
        return -a;
}

float abs(float a)
{
    if(a>0)
        return a;
    else
        return -a;
}

double abs(double a)
{
    if(a>0)
        return a;
    else
        return -a;
}