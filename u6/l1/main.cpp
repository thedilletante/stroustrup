#include <iostream>
#include <string>

int main() {
  std::string input;
  std::getline(std::cin, input);

  const char * input_line = input.c_str();
  unsigned quest_count = 0;

  size_t max_length = input.length();

  for (size_t i = 0; i < max_length; ++i) {
    if (input_line[i] == '?') quest_count++;
  }

  std::cout<<"For: quest_count = "<<quest_count<<"\n";

  quest_count = 0;
  const char * i = input_line;

  while(*i) {
    if (*i++ == '?') quest_count++;
  }

  std::cout<<"While: quest_count = "<<quest_count<<"\n";

  return 0;
}