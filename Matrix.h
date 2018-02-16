// add basic sense checks on dimensions
// + and - will only take matrices of the same size(class)
// * can only take arguments which have matching col/row
// nice and easy!


// add setting operationFailure flag

// add flat structure version of the data (can use for some operations)

// it's only non-member functions which require template declaration on the same line

// is it inconsistent to have some as member functions and some not?
// could I move non-member back to member now that it works?
// or move more to non-member (would this be preferable space-wise?)

// pass by const ref

// add maximum size (to prevent errors)?

// optimisation (may not be required for teensy)

// add way to take initialiser list



#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
class Matrix {
  public:
    bool operationFailure;
    union {
      T data[NUM_ROWS][NUM_COLS];
      T flat[NUM_ROWS * NUM_COLS];
    };

    Matrix();
    void zeroInit();
    void identityInit();
    void customInit(T value);
    Matrix copy();
    Matrix operator+(Matrix m);
    Matrix operator-(Matrix m);
    Matrix operator*(T scalar);
    Matrix operator+(T scalar);
    Matrix operator-(T scalar);
    Matrix operator/(T scalar);
    Matrix inverse();
    Matrix<T, NUM_COLS, NUM_ROWS> transpose();
    void print();
};

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS>::Matrix() {
  zeroInit();
  operationFailure = false;
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
void Matrix<T, NUM_ROWS, NUM_COLS>::customInit(T value) {
  for (uint8_t i = 0; i < NUM_ROWS * NUM_COLS; i++) {
    flat[i] = value;
  }
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
void Matrix<T, NUM_ROWS, NUM_COLS>::zeroInit() {
  for (uint8_t i = 0; i < NUM_ROWS * NUM_COLS; i++) {
    flat[i] = 0.0f;
  }
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
void  Matrix<T, NUM_ROWS, NUM_COLS>::identityInit() {
  for (uint8_t i = 0; i < NUM_ROWS; i++) {
    for (uint8_t j = 0; j < NUM_COLS; j++) {
      if (i == j) {
        data[i][j] = 1.0f;
      }
      else {
        data[i][j] = 0.0f;
      }
    }
  }
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS> Matrix<T, NUM_ROWS, NUM_COLS>::copy() {
  Matrix<T, NUM_ROWS, NUM_COLS> result;
  for (uint8_t i = 0; i < NUM_ROWS * NUM_COLS; i++) {
    result.flat[i] = flat[i];
  }
  return result;
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS> Matrix<T, NUM_ROWS, NUM_COLS>::operator+(Matrix<T, NUM_ROWS, NUM_COLS> m) {
  Matrix<T, NUM_ROWS, NUM_COLS> result;
  for (uint8_t i = 0; i < NUM_ROWS; i++) {
    for (uint8_t j = 0; j < NUM_COLS; j++) {
      result.data[i][j] = data[i][j] + m.data[i][j];
    }
  }
  return result;
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS> Matrix<T, NUM_ROWS, NUM_COLS>::operator-(Matrix<T, NUM_ROWS, NUM_COLS> m) {
  Matrix<T, NUM_ROWS, NUM_COLS> result;
  for (uint8_t i = 0; i < NUM_ROWS; i++) {
    for (uint8_t j = 0; j < NUM_COLS; j++) {
      result.data[i][j] = data[i][j] - m.data[i][j];
    }
  }
  return result;
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS> Matrix<T, NUM_ROWS, NUM_COLS>::operator*(T scalar) {
  Matrix<T, NUM_ROWS, NUM_COLS> result;
  for (uint8_t i = 0; i < NUM_ROWS * NUM_COLS; i++) {
    result.flat[i] = flat[i] * scalar;
  }
  return result;
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS> Matrix<T, NUM_ROWS, NUM_COLS>::operator+(T scalar) {
  Matrix<T, NUM_ROWS, NUM_COLS> result;
  for (uint8_t i = 0; i < NUM_ROWS * NUM_COLS; i++) {
    result.flat[i] = flat[i] + scalar;
  }
  return result;
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS> Matrix<T, NUM_ROWS, NUM_COLS>::operator-(T scalar) {
  Matrix<T, NUM_ROWS, NUM_COLS> result;
  for (uint8_t i = 0; i < NUM_ROWS * NUM_COLS; i++) {
    result.flat[i] = flat[i] - scalar;
  }
  return result;
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS> Matrix<T, NUM_ROWS, NUM_COLS>::operator/(T scalar) {
  Matrix<T, NUM_ROWS, NUM_COLS> result;
  for (uint8_t i = 0; i < NUM_ROWS * NUM_COLS; i++) {
    result.flat[i] = flat[i] / scalar;
  }
  return result;
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_COLS, NUM_ROWS> Matrix<T, NUM_ROWS, NUM_COLS>::transpose() {
  Matrix<T, NUM_COLS, NUM_ROWS> result;
  for (uint8_t i = 0; i < NUM_ROWS; i++) {
    for (uint8_t j = 0; j < NUM_COLS; j++) {
      result.data[j][i] = data[i][j];
    }
  }
  return result;
}

// add setting of operationFailure flag
// skip operations that will be on values known to be zero
// only operates on square matrix
template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS> Matrix<T, NUM_ROWS, NUM_COLS>::inverse() {
  // will only operate on a square matrix
  // for each column, make diagonal element 1, then make ret of column zero

  Matrix<T, NUM_ROWS, NUM_COLS> result;
  result.identityInit();
  Matrix<T, NUM_ROWS, NUM_COLS> temp = copy(); // not going to modify original matrix
  for (uint8_t pivotPosition = 0; pivotPosition < NUM_ROWS; pivotPosition++) {
    // want to use the row with the highest absolute value in the column of the current pivot
    // this can deal with some situations where the diag value is zero
    // NOT IMPLEMENTING NOW

    // first divide the row by the value at pivot to make pivot = 1
    float factor = 1.0f / temp.data[pivotPosition][pivotPosition];
    for (uint8_t j = 0; j < NUM_COLS; j++) {
      temp.data[pivotPosition][j] *= factor;
      result.data[pivotPosition][j] *= factor;  // same operation on result matrix
    }
    // now for each row k (that isn't the pivot row)
    for (uint8_t rowToZero = 0; rowToZero < NUM_ROWS; rowToZero++) {
      if (rowToZero != pivotPosition) {
        // minus (pivot row * [k][pivotPosition]
        float rowFactor = temp.data[rowToZero][pivotPosition];
        for (uint8_t j = 0; j < NUM_COLS; j++) {
          temp.data[rowToZero][j] -= temp.data[pivotPosition][j] * rowFactor;
          result.data[rowToZero][j] -= result.data[pivotPosition][j] * rowFactor;  // same operation on result matrix
        }
      }
    }
  }
  return result;
}


template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
void Matrix<T, NUM_ROWS, NUM_COLS>::print() {
  for (uint8_t i = 0; i < NUM_ROWS; i++) {
    for (uint8_t j = 0; j < NUM_COLS; j++) {
      Serial.print(data[i][j]); Serial.print('\t');
    }
    Serial.print('\n');
  }
  Serial.print('\n');
}



// NOT A MEMBER FUNCTION
template <typename T, uint8_t ROWS_LEFT, uint8_t SHARED_DIMENSION, uint8_t COLS_RIGHT> Matrix<T, ROWS_LEFT, COLS_RIGHT> operator*(const Matrix<T, ROWS_LEFT, SHARED_DIMENSION> a, const Matrix<T, SHARED_DIMENSION, COLS_RIGHT> b) {
  Matrix<T, ROWS_LEFT, COLS_RIGHT> result;
  for (uint8_t i = 0; i < ROWS_LEFT; i++) { // each row in destination matrix
    for (uint8_t j = 0; j < COLS_RIGHT; j++) { // each column in destination matrix
      float accumulator = 0.0f;
      for (uint8_t k = 0; k < SHARED_DIMENSION; k++) {
        accumulator += a.data[i][k] * b.data[k][j];
      }
      result.data[i][j] = accumulator;
    }
  }
  return result;
}


#endif

