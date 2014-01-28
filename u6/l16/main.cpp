#include <iostream>

bool positive(const char** str) {
  if ( **str == '-' ) {
    ++(*str);
    return false;
  }
  return true;
  return ( **str == '-' ) ? ( ++(*str), false ) : true ;
}

int base(const char** str) {
  if ( **str == '0' ){
    ++(*str);
    if ( **str == 'x' ) {
      ++(*str);
      return 16;
    }
    return 8;
  }
  return 10;
}

int getRep(char ch) {
  switch(ch) {
    case '0' : return 0;
    case '1' : return 1;
    case '2' : return 2;
    case '3' : return 3;
    case '4' : return 4;
    case '5' : return 5;
    case '6' : return 6;
    case '7' : return 7;
    case '8' : return 8;
    case '9' : return 9;
    case 'a' : case 'A' : return 10;
    case 'b' : case 'B' : return 11;
    case 'c' : case 'C' : return 12;
    case 'd' : case 'D' : return 13;
    case 'e' : case 'E' : return 14;
    case 'f' : case 'F' : return 15;
    default : return 0;
  }
}

int atoi(const char* str) {
  bool sign = positive(&str);
  int bas = base(&str);
  int result = 0;
  int next = 0;
  while (*str) {
    if ((next = getRep(*str)) < bas) {
      result *= bas;
      result += next;
    }
    ++str;
  }
  if (!sign) result *= -1;
  return result;
}

#define PRINT(A) std::cout<<#A<<" = "<<(A)<<std::endl;

int main() {
  PRINT(atoi("6511"));
  PRINT(atoi("-160"));
  PRINT(atoi("0356"));
  PRINT(atoi("015"));
  PRINT(atoi("-0162"));
  PRINT(atoi("0x1F"));
}
