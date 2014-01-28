#include <iostream>

void printMonth(const char ** names, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    std::cout << names[i] << std::endl;
  }
}

int main() {
  const char * monthes[] = {  "January", "February", "March", 
                        "April", "May", "June", 
                        "July","August", "September", 
                        "October", "November", "December" };
  printMonth(monthes, 12);

  return 0;
}