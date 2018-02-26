# Matrix library

## Main aim
To allow easy and clear use of matrix operations, e.g. A * B. while keeping static (i.e. compile time) memory allocation.

Also include protection against illegal operations e.g. a 3x3 + 2x2, and bounds checking when accessing data elements.

This library uses a template class to support matrices of any size and numeric data type.
Obviously there are serious limitations to the processing capacity of some microcontrollers e.g. 8-bit Atmega328P when it comes to doing a lot of floating point calculations so if speed is an issue then using matrices of floating point numbers may not be an appropriate approach (with any matrix library).
I am currently using this on a Teensy 3.5 (120MHz with FP unit)  - an unoptimised 3x3 matrix inversion routine takes ~14us which is more than sufficient for my needs.

There is an existing matrix library for Arduino [MatrixMath](https://playground.arduino.cc/Code/MatrixMath) which will perform matrix operations on 2D arrays, but it does not cover any of the points above except for static memory allocation and is not 'nice' to use i.e. the user must set up the underlying data structure, must specify the matrix dimensions in every function call and make sure that all operations and accesses are within bounds.

## Use of this library
### Setup
```C++
Matrix<float, 3, 4> X; // Declare a 3 row, 4 column matrix of floats
Matrix<float, 4, 2> Y; // And a 4 row, 2 column matrix of floats
Matrix<int, 5, 1> Z; // And a 5 element column vector of ints
```

### Populating and accessing elements
```C++
A(2, 3) = 1.56f;	// set single element
for (uint8_t i = 0; i < 2; i++) {	// set all elements
  for (uint8_t j = 0; j < 3; j++) {
    A(i, j) = random(-100, 100) / 5.0f;
  }
}
float a = A(1, 2);	// get single element
```

### Basic Operations
The matrices can then be manipulated using the standard operators for scalar and matrix operations.
All operations return a new object. None of the operations (except elementwise access) modify the actual matrix data.
```C++
Matrix<float, 2, 3> C = A + B;
Matrix<float, 3, 4> F = D - E;
Matrix<float, 4, 2> J = G * H;
Matrix<float, 2, 4> K = K * 2.5f;
Matrix<float, 3, 6> M = L.transpose();
Matrix<float, 3, 3> P = N.inverse();
```
The example sketch provided shows working examples of all operations.

### Catching errors
The compiler will catch dimension errors in assignment, add, subtract and multiply matrix operations.
e.g. 
```C++
Matrix<float, 3, 4> A;
Matrix<float, 2, 1> B;
A + B;	// compiler error for the operation (dimensions not matching, 3x4 + 2x1)
Matrix<float, 2, 3> C = A + A;	// compiler error (for the assignment, 2x3 = 3x4)
A * B;	// compiler error for the operation (dimensions not matching, 3x4 * 2x1)
```

The provided operations will NEVER access outside the matrix range.
However you will NOT be prevented from TRYING to do this with the accessor function.
```C++
Matrix<float, 3, 4> A;
A(100, 20) = 4.3f;	// out of bounds, no compile error
float a = A(20, 100);	// out of bounds, no compile error
```
It will not cause a compiler error but the error flag associated with the matrix can be checked to see if there were any out of bounds operations attempted.
```C++
A.getErrorStatus(); // will now have an error status of 1 (index out of range)
```

### Other
A serial print operation is also provided
```C++
A.print();
```
Operations can be chained as normal
```C++
A.transpose().inverse();
```


### Inversion
Uses Gauss-Jordan elimination approach with partial pivoting.
Division within the inversion routine will be done at the data type of the matrix data
- i.e. integer matrices will use integer division - there is no intermediate conversion to float
- inversion of any type of integer matrix is unlikely to work well

### Other notes and considerations
- Does not support matrices of consts
- No consideration/optimisation for sparse matrices
- The error flag does not get reset after a successful operation

