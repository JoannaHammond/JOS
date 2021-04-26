#pragma once
#include "../../memory/heap.h"

template<typename T>
class Matrix {
    public:
    Matrix()
    {
        // empty matrix holder to allow for return of multiplication
    }
    Matrix(uint32_t columns, uint32_t rows)
    {
        this->columns = columns;
        this->rows = rows;
        matrixBuffer = (T*)malloc(columns * rows * sizeof(T));
    }
    Matrix(uint32_t columns, uint32_t rows, T* init)
    {
        this->columns = columns;
        this->rows = rows;
        matrixBuffer = (T*)malloc(columns * rows * sizeof(T));
        FillMatrix(init);
    }
    ~Matrix()
    {
        free(matrixBuffer);
    }

    void FillMatrix(T* values)
    {
        for(uint32_t i = 0; i < columns * rows; i++)
        {
            matrixBuffer[i] = values[i];
        }
    }

    Matrix<T> operator+ (Matrix<T> b)
    {
        if(!CheckSizeMatch(b)) return *this;

        for(int i = 0; i < columns; i++)
        for(int j = 0; j < rows; i++)
        {
            matrixBuffer[(i * columns) + j] = matrixBuffer[(i * columns) + j] + b.matrixBuffer[(i * columns) + j];
        }

        return *this;
    }

    Matrix<T> operator- (Matrix<T> b)
    {
        if(!CheckSizeMatch(b)) return *this;

        for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
        {
            matrixBuffer[(i * columns) + j] = matrixBuffer[(i * columns) + j] - b.matrixBuffer[(i * columns) + j];
        }

        return *this;
    }

    Matrix<T> operator* (Matrix<T> b)
    {
        if(columns != b.rows) return *this;
        
        Matrix<T>* retVal = new Matrix<T>(rows,b.columns);

        for(uint32_t i = 0; i < columns; i++)
        for(uint32_t j = 0; j < b.rows; j++)
        {
            T sum = 0;
            for(uint32_t k = 0; k < rows; k++)
                sum += (matrixBuffer[(columns * i) + k] * b.matrixBuffer[(b.columns * k) + j]);
            retVal->matrixBuffer[(b.columns * i) + j] = sum;
        }

        return *retVal;       
    }

    Matrix<T> operator* (T b)
    {
        for(int i = 0; i < rows; i++)
        for(int j = 0; j < columns; j++)
        {
            matrixBuffer[(i * columns) + j] = matrixBuffer[(i * columns) + j] * b;
        }

        return *this;       
    }

    uint32_t GetColumns() {return columns;}
    uint32_t GetRows() {return rows;}

    T GetElement(uint32_t i, uint32_t j)
    {
        return matrixBuffer[(i * columns) + j];
    }

    void SetElement(uint32_t i, uint32_t j, T value)
    {
        matrixBuffer[(i * columns) + j] = value;
    }

    bool CheckSizeMatch(Matrix<T> b){
        return columns == b.columns && rows == b.rows;
    }

    private:

    uint32_t columns;
    uint32_t rows;

    T* matrixBuffer;
};