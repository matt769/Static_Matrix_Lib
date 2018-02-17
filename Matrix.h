// add basic sense checks on dimensions
// + and - will only take matrices of the same size(class)
// * can only take arguments which have matching col/row
// nice and easy!

// is it inconsistent to have some as member functions and some not?
// could I move non-member back to member now that it works?
// or move more to non-member (would this be preferable space-wise?)

// add maximum size (to prevent errors)?

// optimisation (may not be required for teensy)

// add way to take initialiser list

// try creating some const matrices

#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
class Matrix {
  public:
    Matrix();
    void zeroInit();
    void identityInit();
    Matrix copy();
    T& operator()(uint8_t row, uint8_t col);
    Matrix operator+(const Matrix& m);
    Matrix operator-(const Matrix& m);
    Matrix operator*(T scalar);
    Matrix operator+(T scalar);
    Matrix operator-(T scalar);
    Matrix operator/(T scalar);
    Matrix inverse();
    Matrix<T, NUM_COLS, NUM_ROWS> transpose();
    void print();

  private:
    bool operationFailure;
    union {
      T data[NUM_ROWS][NUM_COLS];
      T flat[NUM_ROWS * NUM_COLS];
    };
    T boundsError;
};

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS>::Matrix() {
  zeroInit();
  operationFailure = false;
  boundsError = -1;
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
T& Matrix<T, NUM_ROWS, NUM_COLS>::operator()(uint8_t row, uint8_t col) {
  if (row < NUM_ROWS && col < NUM_COLS) {
    return data[row][col];
  }
  else {
    return boundsError;
  }
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS> Matrix<T, NUM_ROWS, NUM_COLS>::operator+(const Matrix<T, NUM_ROWS, NUM_COLS> &m) {
  Matrix<T, NUM_ROWS, NUM_COLS> result;
  for (uint8_t i = 0; i < NUM_ROWS; i++) {
    for (uint8_t j = 0; j < NUM_COLS; j++) {
      result.data[i][j] = data[i][j] + m.data[i][j];
    }
  }
  return result;
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS> Matrix<T, NUM_ROWS, NUM_COLS>::operator-(const Matrix<T, NUM_ROWS, NUM_COLS> &m) {
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

// Gauss-Jordan method
// for each column, make diagonal element 1, then makes the rest of the column zero
// only operates on square matrix (will return zero matrix in size of original if not)
// ideally make this enforced by the compiler
// Need to add row swapping
template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS> Matrix<T, NUM_ROWS, NUM_COLS>::inverse() {

  Matrix<T, NUM_ROWS, NUM_COLS> result;
  if (NUM_ROWS != NUM_COLS) {
    operationFailure = true;
    return result;
  }

  result.identityInit();
  Matrix<T, NUM_ROWS, NUM_COLS> temp = copy(); // not going to modify original matrix
  for (uint8_t pivotPosition = 0; pivotPosition < NUM_ROWS; pivotPosition++) {
    // want to use the row with the highest absolute value in the column of the current pivot
    // this can help with numerical stability (avoiding under/overflow)
    // TODO...

    // first divide the row by the value at pivot to make pivot = 1
    if (temp.data[pivotPosition][pivotPosition] == 0) {
      operationFailure = true;
      return result;
    }
    T factor = (T)1 / (temp.data[pivotPosition][pivotPosition]);
    for (uint8_t j = 0; j < NUM_COLS; j++) {
      temp.data[pivotPosition][j] *= factor;
      result.data[pivotPosition][j] *= factor;  // same operation on result matrix
    }
    // now for each row k (that isn't the pivot row)
    // remove the multiple of the current pivot row that will make the element in the pivot column zero
    for (uint8_t rowToZero = 0; rowToZero < NUM_ROWS; rowToZero++) {
      if (rowToZero != pivotPosition) {
        // minus (pivot row * [k][pivotPosition])
        T rowFactor = temp.data[rowToZero][pivotPosition];
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
template <typename T, uint8_t ROWS_LEFT, uint8_t SHARED_DIMENSION, uint8_t COLS_RIGHT> Matrix<T, ROWS_LEFT, COLS_RIGHT> operator*(const Matrix<T, ROWS_LEFT, SHARED_DIMENSION> & a, const Matrix<T, SHARED_DIMENSION, COLS_RIGHT> & b) {
  Matrix<T, ROWS_LEFT, COLS_RIGHT> result;
  for (uint8_t i = 0; i < ROWS_LEFT; i++) { // each row in destination matrix
    for (uint8_t j = 0; j < COLS_RIGHT; j++) { // each column in destination matrix
      T accumulator = 0;
      for (uint8_t k = 0; k < SHARED_DIMENSION; k++) {
        accumulator += a(i,k) * b(k,j);
      }
      result(i,j) = accumulator;
    }
  }
  return result;
}


#endif

