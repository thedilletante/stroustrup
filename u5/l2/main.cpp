#include <iostream>

typedef char check_t;

check_t gA;
check_t gB;
check_t gC;
check_t gD;

int main() {
  check_t a;
  check_t b;
  check_t c;
  check_t d;

  check_t * p = new check_t(1);

  std::cout<<"Global :\n";
  std::cout<<&gA<<"\t"<<&gB<<"\t"<<&gC<<"\t"<<&gD<<"\n";

  std::cout<<"Auto :\n";
  std::cout<<&a<<"\t"<<&b<<"\t"<<&c<<"\t"<<&d<<"\n";

  std::cout<<"Heap :\n";
  std::cout<<p<<"\n";

  delete p;
  return 0;
}