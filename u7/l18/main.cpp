#include <iostream>

int factorial(int n) {
  int delta = n > 0 ? -1 : 1;
  int result = 1;
  for ( int i = n; i; i += delta ) {
    result *= i;
  }
  return result;
}

int main() {
  std::cout<<factorial(1)<<std::endl;
  std::cout<<factorial(0)<<std::endl;
  std::cout<<factorial(2)<<std::endl;
  std::cout<<factorial(4)<<std::endl;
  std::cout<<factorial(9)<<std::endl;
  std::cout<<factorial(-1)<<std::endl;
  std::cout<<factorial(-3)<<std::endl;
  std::cout<<factorial(-6)<<std::endl;
  return 0;
}