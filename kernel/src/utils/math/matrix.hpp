#pragma once
#include "../../memory/heap.h";

template<typename T>
class Matrix {
    public:
    Matrix(uint32_t width, uint32_t height)
    {
        this->width = width;
        this->height = height;
        matrixbuffer = malloc(width * height * sizeof(T));
    }
    ~Matrix()
    {
        free(matrixbuffer);
    }

    Matrix operator+ ();
    Matrix operator- ();
    Matrix operator* ();
    Matrix operator/ ();
    Matrix DotProduct (Matrix b);
    Matrix CrossProduct (Matrix b);

    private:

    uint32_t = width;
    uint32_t = height;

    T* matrixbuffer;
}