#include "Matrix.h"


Matrix<float, 3, 4> A;  // Declare a 3 row, 4 column matrix of floats
Matrix<float, 3, 4> B;
Matrix<float, 4, 2> D;
Matrix<float, 3, 3> L;

Matrix<int, 2, 2> W;  // Declare a 2 row, 24 column matrix of integers


void test() {
  randomSeed(0);

  // Access matrix elements - NOTE indexes start at 0
  float a = A(1, 2);
  A(2, 3) = 1.56f;
  Serial.print("A error status: "); Serial.println(A.getErrorStatus()); // error status of 0 (no errors)
  float b = A(100, 20); // trying to access outside the matrix
  Serial.print("A error status after out of range access: "); Serial.println(A.getErrorStatus()); // now we have error status of 1 (index out of range)
  Serial.println();

  // Populate base matrices
  Serial.println("A:");
  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      A(i, j) = random(-100, 100) / 5.0f;
    }
  }
  A.print();

  Serial.println("B:");
  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      B(i, j) = random(-100, 100) / 5.0f;
    }
  }
  B.print();

  Serial.println("D:");
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 2; j++) {
      D(i, j) = random(-100, 100) / 5.0f;
    }
  }
  D.print();

  Serial.println("L:");
  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t j = 0; j < 3; j++) {
      L(i, j) = random(-100, 100) / 5.0f;
    }
  }
  L.print();

  // Basic operations
  Serial.println("A + B");
  Matrix<float, 3, 4> C = A + B;
  C.print();

  Serial.println("A * D");
  Matrix<float, 3, 2> E = A * D;
  E.print();

  Serial.println("A - B");
  C = A - B;
  C.print();

  Serial.println("A * 1.23");
  C = A * 1.23f;
  C.print();

  Serial.println("D.copy()");
  Matrix<float, 4, 2> H = D.copy();
  H.print();

  Serial.println("L.inverse()");
  L.inverse().print();

  Serial.println("L.transpose()");
  L.transpose().print();

  // Inversion error
  Matrix<float, 2, 2> M;  // filled with zeros so definitely not invertible
  Serial.print("M error status: ");
  Serial.println(M.getErrorStatus()); // error status of 0 (no errors)
  Matrix<float, 2, 2> Minv = M.inverse();  // try to invert
  Serial.print("M error status after inversion attempt: ");
  Serial.println(M.getErrorStatus()); // error status of 2 (inversion error)
  // this means that the data in Minv will not be ok to use

  Serial.print("D error status: ");
  Serial.println(D.getErrorStatus()); // error status of 0 (no errors)
  Matrix<float, 4, 2> Dinv = D.inverse();
  Serial.print("D error status after inversion attempt: ");
  Serial.println(D.getErrorStatus()); // error status of 2 (inversion error)
  // this means that the data in Dinv will not be ok to use

  // Longer expressions
  Serial.println();
  Serial.println("A*B.transpose() + L.inverse()*2");
  Matrix<float, 3, 3> X = A * B.transpose() + L.inverse() * 2;
  X.print();

  L.print();
  L.inverse().print();
  L.print();
  L.inverseNEW().print();

  // And the following will fail to compile
  //  Matrix<float, 2, 2> J = A + B;  // assigning to incorrect result size
  //  Matrix<float, 3, 2> K = D * B;  // D.cols and B.rows don't match
}

void testNewInverse() {

  Serial.println("L:");
  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t j = 0; j < 3; j++) {
      L(i, j) = random(-100, 100) / 5.0f;
    }
  }
  L.print();
  L.inverse().print();
  L.inverseNEW().print();

  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t j = 0; j < 3; j++) {
      L(i, j) = random(-100, 100) / 5.0f;
    }
  }
  L.print();
  L.inverse().print();
  L.inverseNEW().print();

  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t j = 0; j < 3; j++) {
      L(i, j) = random(-100, 100) / 5.0f;
    }
  }
  L.print();
  L.inverse().print();
  L.inverseNEW().print();

  Matrix<float, 3, 3> X;
  Serial.println(micros());
  X = L.inverse();
  Serial.println(micros());

  Serial.println(micros());
  X = L.inverseNEW();
  Serial.println(micros());

}


void setup() {
  Serial.begin(230400);
  delay(1000);

  testNewInverse();
  //  test();

}

void loop() {}

