
typedef unsigned char uchar;
typedef const uchar cuchar;
typedef int * pint;
typedef char ** ppchar;
typedef char (*parchar)[];
typedef int * p7int[7];
typedef p7int * pp7int;
typedef int * p8x7int[8][7];

int main() {
  uchar b = 'a';
  cuchar c = 'b';
  pint d = 0;
  ppchar pc = 0;
  parchar parc = 0;
  p7int p7 = {0};
  pp7int pp7 = &p7;
  p8x7int p8x7 = {{0}};
}