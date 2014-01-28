#include <iostream>

char getIRep(int a) {
  switch(a) {
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
    case 10: return 'A';
    case 11: return 'B';
    case 12: return 'C';
    case 13: return 'D';
    case 14: return 'E';
    case 15: return 'F';
    default : return 0;
  }
}

char * addSign(int i, char b[]) {
  if (i < 0) *b++ = '-';
  return b;
}

char * addBase(char b[], unsigned base = 10) {
  switch(base) {
    case 8: *b++ = '0'; break;
    case 16: *b++ = '0'; *b++ = 'x'; break;
  }
  return b;
}

unsigned insert(char * b, int i, unsigned base, unsigned step = 0) {
  unsigned count = step;
  if (i) {
    count = insert(b, i / base, base, step + 1);
    char inserter = getIRep( i % base );
    b[count - step - 1] = inserter;
  }
  return count;
}

char * itoa(int i, char b[], unsigned base = 10) {
  char * begin = b;
  if (i) {
    b = addSign(i, b);
    if (i < 0) i *= -1;
    b = addBase(b, base);
    unsigned length = insert(b, i, base);
    b += length;
  }
  else {
    *b++ = '0';
  }
  *b = '\0';
  return begin;
}

int main() {
  char a[10];
  std::cout<<itoa(-612, a)<<std::endl;
  std::cout<<itoa(-12, a, 16)<<std::endl;
  return 0;
}