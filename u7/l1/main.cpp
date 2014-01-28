#include <iostream>

void f1( char * ch, int & d );

typedef void (* v_pc_ri)(char *, int &);

v_pc_ri f2(v_pc_ri fn);

v_pc_ri pf1 = f1;

int main() {
  v_pc_ri my_fn = f2(pf1);
  char str[] = "Hello";
  int a = 5;
  my_fn(str, a);
  return 0;
}

void f1( char * ch, int & d ){
  std::cout<<ch<<" : "<<d<<"\n";
}

v_pc_ri f2(v_pc_ri fn) {
  return fn;
}