#include <iostream>
#include "tmatrix.h"

void main()
{
  TDynamicMatrix<int> a(2), b(2), c(2);
  TDynamicVector<int> v(2),v1(3);
  int i, j;
  v[0] = 1;
  v[1] = 2;
  v1[0] = 2;
  v1[1] = 3;
  v1[2] = 4;
  cout << "Testing matrix:"<< endl;
  for (i = 0; i < 2; i++)
      for (j = 0; j < 2; j++)
      {
          a[i][j] = i + 10 + j;
          b[i][j] = (i + 10 + j) * 2;
      }
  cout << "Matrix a: " << endl << a << endl;
  cout << "Matrix b: " << endl << b << endl;
  cout << "Matrix c:" << endl << c << endl;
  cout << "Matrix a * b:" << endl << (a * b) << endl;
  cout << "Matrix a - b:" << endl << (b - a) << endl;
  cout << "Matrix a + b:" << endl << (a+b) << endl;
  cout << "Vector v:" << endl << v << endl;
  cout << "Vector v1:" << endl << v1 << endl;
  //cout << "Vector v*v1:" << endl << v*v1 << endl;
  //cout << "Multip a*v:" << endl << a*v << endl;
  v = v1;
  cout << "v = v1" << endl << v << endl;
  c = a;
  cout << "Matrix c = a:" << endl << c << endl;
}
