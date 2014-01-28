int main() {
  char * ch = 0;
  int ar[10] = {1};
  int (*par)[10] = &ar;
  char (*strs)[] = 0;
  char ** ppch = &ch;
  const int cint = 10;
  const int * pcint = &cint;
  int * const cpint = ar;
}