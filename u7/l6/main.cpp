#include <iostream>
#include <algorithm>


typedef int(*CFT)(const void*, const void*);

void ssort(void* base, size_t n, size_t sz, CFT cmp) {
  return std::qsort(base, n, sz, cmp);
}

int mycmp(const void* a, const void* b) {
  return *(static_cast<const char*>(a)) - *(static_cast<const char*>(b));
}

int main() {
  char ar[] = "hfdskasdfbvka";
  ssort(ar, sizeof(ar), 1, mycmp);
  for (unsigned i = 0; i < sizeof(ar); ++i) {
    std::cout<<ar[i]<<"\t";
  }
  std::cout<<"\n";
  return 0;
}