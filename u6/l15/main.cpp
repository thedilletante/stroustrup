#include <iostream>

void send(int* to, int* from, int count) {
  int n = (count + 7) / 8;
  switch (count % 8) {
    case 0: do {  *to++ = *from++;
    case 7:       *to++ = *from++;
    case 6:       *to++ = *from++;
    case 5:       *to++ = *from++;
    case 4:       *to++ = *from++;
    case 3:       *to++ = *from++;
    case 2:       *to++ = *from++;
    case 1:       *to++ = *from++;
              } while (--n > 0);
  }
}

void print(int * ar, int count) {
  while (count-- > 0) {
    std::cout<<*ar++<<"\t";
  }
  std::cout<<"\n";
}

int main() {
  int from[] = {1,2,3,4,5,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,27,26,28};
  int to[50] = {0};

  send(to, from, 16);
  print(to, 20);


  send(to, from, 8);
  print(to, 20);


  send(to, from, 0);
  print(to, 20);


  send(to, from, 24);
  print(to, 30);
  return 0;
}