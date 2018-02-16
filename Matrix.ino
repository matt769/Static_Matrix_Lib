#include "Matrix.h"

// there is nothing preventing access outside the data area
// should I overload the accessors()

// all operations here take ~7us on the Teensy 3.5
// except inverse which is ~14us

// on ATMEGA328P, between 500us and 800us for the below operations
// except inverse which is ~1400us

// inversion will probably not work well with non floats

// it's only non-member functions which require template declaration on the same line

Matrix<float, 3, 4> A;
Matrix<float, 3, 4> B;
Matrix<float, 4, 2> D;

void setup() {
  Serial.begin(230400);
  delay(2000);
  randomSeed(0);

  for (uint8_t i = 0; i < 12; i++) {
    A.flat[i] = random(-100, 100) / 5.0f;
  }
  A.print();

  for (uint8_t i = 0; i < 12; i++) {
    B.flat[i] = random(-100, 100) / 5.0f;
  }
  B.print();

  for (uint8_t i = 0; i < 8; i++) {
    D.flat[i] = random(-100, 100) / 5.0f;
  }
  D.print();


  Serial.println(micros());
  Matrix<float, 3, 4> C = A + B;
  Serial.println(micros());
  C.print();
  Serial.println(micros());
  Matrix<float, 3, 2> E = A * D;
  Serial.println(micros());
  E.print();
  Serial.println(micros());
  Matrix<float, 3, 4> F = A - B;
  Serial.println(micros());
  F.print();
  Serial.println(micros());
  Matrix<float, 3, 4> G = A * 1.23f;
  Serial.println(micros());
  G.print();
  Serial.println(micros());
  Matrix<float, 4, 2> H = D.copy();
  Serial.println(micros());
  H.print();

  Matrix<float, 3, 3> L;
  for (uint8_t i = 0; i < 9; i++) {
    L.flat[i] = random(-100, 100) / 5.0f;
  }
  L.print();
  Matrix<float, 3, 3> Linv;
  Serial.println(micros());
  Linv = L.inverse();
  Serial.println(micros());
  Linv.print();

  delay(1000);
  Matrix<int, 3, 4> M;
  for (uint8_t i = 0; i < 9; i++) {
    M.flat[i] = (int)random(-100, 100) / 5.0f;
  }
  M.print();
  Matrix<int, 4, 3> N;
  for (uint8_t i = 0; i < 9; i++) {
    N.flat[i] = (int)random(-100, 100) / 5.0f;
  }
  N.print();
  
  Matrix<int, 3, 3> P;
  Serial.println(micros());
  P = M * N;
  Serial.println(micros());
  P.print();




  // the following should fail to compile
  //  Matrix<float, 2, 2> J = A + B;  // assigning to incorrect result size
  //  Matrix<float, 3, 2> K = D * B;  // D.cols and B.rows don't match
  //  H.inverse(); // will give compiler warning of underfined behaviour (not square matrix)

}

void loop() {

}

