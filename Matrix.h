#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>

#define MATRIX_INDEX_OUT_OF_RANGE 1
#define MATRIX_INVERSION_FAILURE 2

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
class Matrix {
  public:
    Matrix();
    void zeroInit();
    void identityInit();
    Matrix copy();
    T getElement(const uint8_t row, const uint8_t col) const; // no bounds checking
    T& setElement(const uint8_t row, const uint8_t col); // no bounds checking
    T& operator()(const uint8_t row, const uint8_t col);
    Matrix operator+(const Matrix& m);
    Matrix operator-(const Matrix& m);
    Matrix operator*(T scalar);
    Matrix operator+(T scalar);
    Matrix operator-(T scalar);
    Matrix operator/(T scalar);
    Matrix inverse();
    Matrix<T, NUM_COLS, NUM_ROWS> transpose();
    uint8_t getErrorStatus();
    void print();

  private:
    uint8_t operationFailure;
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
T Matrix<T, NUM_ROWS, NUM_COLS>::getElement(const uint8_t row, const uint8_t col) const {
    return data[row][col];
}


template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
T& Matrix<T, NUM_ROWS, NUM_COLS>::operator()(const uint8_t row, const uint8_t col) {
  if (row < NUM_ROWS && col < NUM_COLS) {
    return data[row][col];
  }
  else {
    operationFailure |= MATRIX_INDEX_OUT_OF_RANGE;
    return boundsError;
  }
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
T& Matrix<T, NUM_ROWS, NUM_COLS>::setElement(const uint8_t row, const uint8_t col) {
    return data[row][col];
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
      result.setElement(j, i) = data[i][j];
    }
  }
  return result;
}

// Gauss-Jordan method
// for each column, make diagonal element (the pivot) equal 1, then makes the rest of the column zero
// only operates on square matrix (will return zero matrix in size of original if not)
// the 'pivotrow' or 'pivotcolumn' if referred to is just the row/col of the current pivot point
template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS> Matrix<T, NUM_ROWS, NUM_COLS>::inverse() {

  Matrix<T, NUM_ROWS, NUM_COLS> result;
  if (NUM_ROWS != NUM_COLS) {
    operationFailure |= MATRIX_INVERSION_FAILURE;
    return result;
  }

  result.identityInit();
  Matrix<T, NUM_ROWS, NUM_COLS> temp = copy(); // not going to modify original matrix
  uint8_t rowSwaps[NUM_ROWS];
  T tempSwapValue;
  // want to use the row with the highest absolute value in the column of the current pivot
  // this can help with numerical stability (avoiding under/overflow)
  // first find the row with the highest abs value
  for (uint8_t pivotPosition = 0; pivotPosition < NUM_ROWS; pivotPosition++) {
    uint8_t rowWithMaxValue = pivotPosition;
    T maxAbsValue = abs(temp.data[pivotPosition][pivotPosition]);
    for (uint8_t i = 0; i < NUM_ROWS; i++) {
      if (i != pivotPosition) {
        if (abs(temp.data[i][pivotPosition]) > maxAbsValue) {
          rowWithMaxValue = i;
          maxAbsValue = abs(temp.data[i][pivotPosition]);
        }
      }
    }
	// if it's not the current pivot row then we need to swap rows
    if (rowWithMaxValue != pivotPosition) {
      for (uint8_t j = 0; j < NUM_COLS; j++) {
        tempSwapValue = temp.data[rowWithMaxValue][j];
        temp.data[rowWithMaxValue][j] = temp.data[pivotPosition][j];
        temp.data[pivotPosition][j] = tempSwapValue;
		// and we do this for the result matrix as well
        tempSwapValue = result.data[rowWithMaxValue][j];
        result.data[rowWithMaxValue][j] = result.data[pivotPosition][j];
        result.data[pivotPosition][j] = tempSwapValue;
      }
    }
    rowSwaps[pivotPosition] = rowWithMaxValue; // record the swap even if none for easier reversal

    // now divide the row by the value at pivot to make pivot = 1
	// check for pivot = 0 first in which case can't invert
    if (temp.data[pivotPosition][pivotPosition] == 0) {
      operationFailure = true;
      return result;
    }
    T factor = (T)1 / (temp.data[pivotPosition][pivotPosition]);
    for (uint8_t j = 0; j < NUM_COLS; j++) {
      temp.data[pivotPosition][j] *= factor;
      result.data[pivotPosition][j] *= factor;  // same operation on result matrix
    }
    // now for each row (that isn't the pivot row)
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

  // now do column swaps (in reverse order) on result to reverse effect of row swaps
  for (int8_t i = NUM_ROWS; i >= 0; i--) {
    // if there was a swap
    if (rowSwaps[i] == i) {
      for (uint8_t j = 0; j < NUM_COLS; j++) {
        tempSwapValue = result.data[i][j];
        result.data[i][j] = result.data[rowSwaps[i]][j];
        result.data[rowSwaps[i]][j] = tempSwapValue;
      }
    }
  }

  return result;
}



template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
void Matrix<T, NUM_ROWS, NUM_COLS>::print() {
  for (uint8_t i = 0; i < NUM_ROWS; i++) {
    for (uint8_t j = 0; j < NUM_COLS; j++) {
      Serial.print(data[i][j], 3); Serial.print('\t');
    }
    Serial.print('\n');
  }
  Serial.print('\n');
}

template <typename T, uint8_t NUM_ROWS, uint8_t NUM_COLS>
uint8_t Matrix<T, NUM_ROWS, NUM_COLS>::getErrorStatus() {
  return operationFailure;
}


// NOT A MEMBER FUNCTION
template <typename T, uint8_t ROWS_LEFT, uint8_t SHARED_DIMENSION, uint8_t COLS_RIGHT> Matrix<T, ROWS_LEFT, COLS_RIGHT> operator*(const Matrix<T, ROWS_LEFT, SHARED_DIMENSION> & a, const Matrix<T, SHARED_DIMENSION, COLS_RIGHT> & b) {
  Matrix<T, ROWS_LEFT, COLS_RIGHT> result;
  for (uint8_t i = 0; i < ROWS_LEFT; i++) { // each row in destination matrix
    for (uint8_t j = 0; j < COLS_RIGHT; j++) { // each column in destination matrix
      T accumulator = 0;
      for (uint8_t k = 0; k < SHARED_DIMENSION; k++) {
        accumulator += a.getElement(i, k) * b.getElement(k, j);
      }
      result.setElement(i, j) = accumulator;
    }
  }
  return result;

}

#endif

