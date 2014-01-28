#include <iostream>

void print(int value, int base = 10);
void nonZeroPrint(int value, int base);
char getCh(int value);

int main() {
  print(31);
  print(31, 10);
  print(31, 16);
  print(31, 2);
  return 0;
}

void print(int value, int base) {
  if ( value ) {
    nonZeroPrint( value, base );
  }
  else {
    std::cout<<value;
  }
  std::cout<<std::endl;
}

void nonZeroPrint(int value, int base) {
  if ( value ) {
    nonZeroPrint( value / base, base );
    std::cout << getCh( value % base );
  }
}

char getCh(int value) {
  switch (value) {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    case 10: return 'a';
    case 11: return 'b';
    case 12: return 'c';
    case 13: return 'd';
    case 14: return 'e';
    case 15: return 'f';
  }
  return '\0';
}