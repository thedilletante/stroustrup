#include <iostream>
#include <cstring>

int main() {
  char str[] = "a short string";
  std::cout<<"size of string \""<<str<<"\" is "<<sizeof(str)<<" bytes\n";
  std::cout<<"length of string \""<<str<<"\" is "<<strlen(str)<<" characters\n";
  return 0;
}