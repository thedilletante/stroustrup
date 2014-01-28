#include <iostream>
#include <cstring>

char * cat(const char * arg1, const char * arg2)
{
  size_t len1 = strlen(arg1);
  char * result = new char[len1 + strlen(arg2) + 1];
  strcpy(result, arg1);
  strcpy(result + len1, arg2);
  return result;
}

int main()
{
  char * ch = cat("Hello,", " World!");
  std::cout<<ch<<"\n";
  delete[] ch;
  return 0;
}