#include <iostream>

#define PREX(EX) std::cout<<#EX<<" === "<<(EX)<<std::endl

int f(int x, int y) {
  return x + y;
}

int main() {
  int a = 0, b = 0, c = 0, d = 0, x = 0, i = 0;
  int ar[5][3] = { {0} };
  int * p = &b;
  int *pd = &d;

  PREX(a = b + c * d << 2 & 8);
  PREX(a & 077 != 3);
  PREX(a == b || a == c && c < 5);
  PREX(c = x != 0);
  PREX(0 <= i < 7);
  PREX(f(1, 2) + 3);
  PREX(a = -1 + +b- -5);
  PREX(a = b == c ++);
  PREX(a = b = c = 0);
  PREX(ar[4][2] *= *p ? c : * pd * 2);
  PREX( (a - b, c = d) );

  std::cout<<"_______WITH THE BRACKETS______\n";


  PREX(a = (b + (((c * d) << 2) & 8)));
  PREX(a & (077 != 3));
  PREX(((a == b) || ((a == c) && (c < 5))));
  PREX((c = (x != 0)));
  PREX(((0 <= i) < 7));
  PREX(((f(1, 2)) + 3));
  PREX(a = (-1 + (+b - -5)));
  PREX(a = (b == (c ++)));
  PREX(a = (b = (c = 0)));
  PREX(ar[4][2] *= (*p ? c : (* pd * 2)));
  PREX( ((a - b), (c = d)) );

  return 0;
}