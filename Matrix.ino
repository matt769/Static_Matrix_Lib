#include "Matrix.h"

// test on arduino and teensy
// check results and performance



Matrix<float, 3, 4> A;
Matrix<float, 3, 4> B;
Matrix<float, 4, 2> D;

void setup() {
  Matrix<float, 3, 4> C = A + B;
  C.print();
  Matrix<float, 3, 2> E = A * D;
  E.print();
  Matrix<float, 3, 4> F = A - B;
  F.print();
  Matrix<float, 3, 4> G = A * 1.23f;
  G.print();
  Matrix<float, 4, 2> H = D.copy();
  H.print();
  Matrix<float, 4, 2> I;
  I.identityInit();
  I.inverse().print();  // need to add proper check

  
}

void loop() {

}

