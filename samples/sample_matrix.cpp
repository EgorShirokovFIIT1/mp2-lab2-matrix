#include <iostream>
#include "tmatrix.h"

void main()
{
  TDynamicMatrix<int> a(2), b(2), c(2);
  int i, j;

  cout << "Testing matrix:"<< endl;
  for (i = 0; i < 2; i++)
      for (j = i; j < 2; j++)
      {
          a[i][j] = i + 10 + j;
          b[i][j] = (i + 10 + j) * 2;
      }
  c = a + b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;
}
