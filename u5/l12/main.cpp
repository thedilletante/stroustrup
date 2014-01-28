#include <iostream>
#include <string>
#include <algorithm>

size_t repeatQnt(const char * str, const char pair[2]) {
  size_t result = 0;
  bool next = false;
  for (size_t i = 0; str[i]; ++i) {
    if (next && str[i] == pair[1]) {
      next = false;
      ++result;
    }
    else {
      next = (str[i] == pair[0]);
    }
  }
  return result;
}

size_t repeatQnt(const std::string & str, const std::string & pair) {
  size_t result = 0;
  size_t cur = 0;
  while ((cur = str.find(pair, cur)) != std::string::npos) {
    cur += pair.length();
    ++result;
  }
  return result;
}

int main() {
  const char * str = "ababaaabaab";
  std::cout<<repeatQnt(str, "ab")<<std::endl;
  std::string s("ababaaabab");
  std::string in("ab");
  std::cout<<repeatQnt(s, in)<<std::endl;
  return 0;
}