// add basic sense checks on dimensions
// although compiler should catch many

// add setting operationFailure flag

// add flat structure version of the data

// change back to bytes

#ifndef MATRIX_H
#define MATRIX_H

template <typename T, int NUM_ROWS, int NUM_COLS>
class Matrix {
  public:
        bool operationFailure;
    T data[NUM_ROWS][NUM_COLS];
    Matrix();
    void zeroInit();
    //    void identityInit();
    //    void customInit(T value);
    //    Matrix copy();
    //    Matrix operator+(Matrix m);
    //    Matrix operator-(Matrix m);
    //    Matrix operator*(T scalar);
    //    Matrix inverse();
    //    void print();
};


//Matrix operator*(Matrix m);
//Matrix transpose();


#endif






