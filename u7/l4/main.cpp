#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    std::ifstream file(argv[i]);
    if (file.is_open()) {
      std::cout<<"_________________\n"<<argv[i]<<"\n_________________\n";
      char ch;
      while(file.get(ch)) std::cout<<ch;
    }
    else {
      std::cout<<"_________________\nfile "<<argv[i]<<" can`t be readed\n";
    }
  }
  return 0;
}