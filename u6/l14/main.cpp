#include <iostream>
#include <string>
#include <locale>

class mb_string : public std::wstring
{
public:
  mb_string revert()
  {
    mb_string revert;
    revert.reserve( length() );
    std::wstring::const_iterator cur = end();
    std::wstring::const_iterator beg = begin();
    while(cur-- != beg)
      revert += *cur;
    return revert;
  }
};

int main()
{
  std::setlocale(LC_ALL, "ru_RU.UTF-8");
  mb_string a;
  while(std::wcin>>a)
  {
    std::wcout<<a.revert()<<L" ";
  }
  std::cout<<std::endl;
  return 0;
}