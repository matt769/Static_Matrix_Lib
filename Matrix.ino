#include "Matrix.h"

Matrix<float, 3, 5> A;
Matrix<float, 3, 5> B;
Matrix<float, 5, 2> D;

void setup() {
  Matrix<float, 3, 5> C = A + B;
  Serial.println(C.data[0][0]);
  Matrix<float, 3, 2> E = A * D;
  Serial.println(E.data[0][0]);  
}

void loop() {

}

