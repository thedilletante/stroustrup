int main() {
  const unsigned size = 100;
  char ar[size];
  for (unsigned j = 0; j < 1000; ++j) {
    for (unsigned i = 0; i < size; ++i) {
      *(ar + i) = 0;
    }
  }
/*
  for (unsigned i = 0; i < size; ++i) {
    ar[i] = 0;
  }
  for (unsigned i = 0; i < size; ++i) {
    *(ar + i) = 0;
  }
*/
  return 0;
}