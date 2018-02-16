#include <Arduino.h>
#include "Matrix.h"

template <typename T, int NUM_ROWS, int NUM_COLS>
Matrix<T, NUM_ROWS, NUM_COLS>::Matrix() {
  zeroInit();
  operationFailure = false;
}

//void Matrix::customInit(float value) {
//  for (uint8_t i = 0; i < numRows; i++) {
//    for (uint8_t j = 0; j < numCols; j++) {
//      data[i][j] = value;
//    }
//  }
//}

template <typename T, int NUM_ROWS, int NUM_COLS>
void Matrix<T, NUM_ROWS, NUM_COLS>::zeroInit() {
  for (uint8_t i = 0; i < NUM_ROWS; i++) {
    for (uint8_t j = 0; j < NUM_COLS; j++) {
      data[i][j] = 0.0f;
    }
  }
}
//
//void Matrix::identityInit() {
//  for (uint8_t i = 0; i < numRows; i++) {
//    for (uint8_t j = 0; j < numCols; j++) {
//      if (i == j) {
//        data[i][j] = 1.0f;
//      }
//      else {
//        data[i][j] = 0.0f;
//      }
//    }
//  }
//}
//
//// returns a copy of the matrix
//Matrix Matrix::copy() {
//  Matrix result(numRows, numCols);
//  for (uint8_t i = 0; i < numRows; i++) {
//    for (uint8_t j = 0; j < numCols; j++) {
//      result.data[i][j] = data[i][j];
//    }
//  }
//  return result;
//}
//
//
//
//Matrix Matrix::operator+(Matrix m) {
//  Matrix result(numRows, numCols);
//  for (uint8_t i = 0; i < numRows; i++) {
//    for (uint8_t j = 0; j < numCols; j++) {
//      result.data[i][j] = data[i][j] + m.data[i][j];
//    }
//  }
//  return result;
//}
//
//Matrix Matrix::operator-(Matrix m) {
//  Matrix result(numRows, numCols);
//  for (uint8_t i = 0; i < numRows; i++) {
//    for (uint8_t j = 0; j < numCols; j++) {
//      result.data[i][j] = data[i][j] - m.data[i][j];
//    }
//  }
//  return result;
//}
//
//Matrix Matrix::operator*(Matrix m) {
//  uint8_t newRows = numRows;
//  uint8_t newCols = m.numCols;
//  uint8_t sharedDimension = numCols; // no. of cols in 1st matrix will be same as no. of rows in 2nd
//  Matrix result(newRows, newCols);
//  for (uint8_t i = 0; i < newRows; i++) { // each row in destination matrix
//    for (uint8_t j = 0; j < newCols; j++) { // each column in destination matrix
//      float accumulator = 0.0f;
//      for (uint8_t k = 0; k < sharedDimension; k++) {
//        accumulator += data[i][k] * m.data[k][j];
//      }
//      result.data[i][j] = accumulator;
//    }
//  }
//  return result;
//}
//
//Matrix Matrix::operator*(float scalar) {
//  Matrix result(numRows, numCols);
//  for (uint8_t i = 0; i < numRows; i++) {
//    for (uint8_t j = 0; j < numCols; j++) {
//      result.data[i][j] = data[i][j] * scalar;
//    }
//  }
//  return result;
//}
//
//
//void Matrix::print() {
//  for (uint8_t i = 0; i < numRows; i++) {
//    for (uint8_t j = 0; j < numCols; j++) {
//      Serial.print(data[i][j]); Serial.print('\t');
//    }
//    Serial.print('\n');
//  }
//  Serial.print('\n');
//}
//
//
//Matrix Matrix::transpose() {
//  Matrix result(numCols, numRows);
//  for (uint8_t i = 0; i < numRows; i++) {
//    for (uint8_t j = 0; j < numCols; j++) {
//      result.data[j][i] = data[i][j];
//    }
//  }
//  return result;
//}
//
//// add setting of operationFailure flag
//// skip operations that will be on values known to be zero
//Matrix Matrix::inverse() {
//  // will only operate on a square matrix
//  // for each column, make diagonal element 1, then make ret of column zero
//
//  Matrix result(numRows, numCols);
//  result.identityInit();
//  Matrix temp = copy(); // not going to modify original matrix
//  for (uint8_t pivotPosition = 0; pivotPosition < numRows; pivotPosition++) {
//    // want to use the row with the highest absolute value in the column of the current pivot
//    // this can deal with some situations where the diag value is zero
//    // NOT IMPLEMENTING NOW
//    
//    // first divide the row by the value at pivot to make pivot = 1
//    float factor = 1.0f / temp.data[pivotPosition][pivotPosition];
//    for (uint8_t j = 0; j < numCols; j++) {
//      temp.data[pivotPosition][j] *= factor;
//      result.data[pivotPosition][j] *= factor;  // same operation on result matrix
//    }
//    // now for each row k (that isn't the pivot row)
//    for (uint8_t rowToZero = 0; rowToZero < numRows; rowToZero++) {
//      if (rowToZero != pivotPosition) {
//        // minus (pivot row * [k][pivotPosition]
//        float rowFactor = temp.data[rowToZero][pivotPosition];
//        for (uint8_t j = 0; j < numCols; j++) {
//          temp.data[rowToZero][j] -= temp.data[pivotPosition][j] * rowFactor;
//          result.data[rowToZero][j] -= result.data[pivotPosition][j] * rowFactor;  // same operation on result matrix
//        }
//      }
//    }
//  }
//  return result;
//}
