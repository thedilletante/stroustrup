#include <iostream>

void swapPtr(int * a, int * b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void swapLinks(int & a, int & b) {
  int tmp = a;
  a = b;
  b = tmp;
}

int main() {
  int a = 10;
  int b = 15;
  std::cout<<a<<" "<<b<<"\n";
  swapPtr(&a, &b);
  std::cout<<a<<" "<<b<<"\n";
  swapLinks(a, b);
  std::cout<<a<<" "<<b<<"\n";
  return 0;
}