#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>

typedef std::vector<std::string> words_t;

void printWords(const words_t & words) {
  for (words_t::const_iterator cur = words.begin(), end = words.end();
      cur != end; ++cur) {
    std::cout<<*cur<<"\n";
  }
}

int main() {
  std::string tmp;
  words_t words;
  
  while (tmp != "Quit") {
    if (tmp != "" && std::find(words.begin(), words.end(), tmp) == words.end()) {
      words.push_back(tmp);
    }
    std::getline(std::cin, tmp);
  }
  std::sort(words.begin(), words.end());

  printWords(words);

  return 0;
}