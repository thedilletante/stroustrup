#include <iostream>

size_t strlen(const char * str)
{
  size_t len = 0;
  while(*str++) ++len;
  return len;
}

char * strcpy(const char * src, char * dst)
{
  char * start = dst;
  while(*src)
    *dst++ = *src++;
  return start;
}

int strcmp(const char * str1, const char * str2)
{
  for ( char a = *str1, b = *str2 ; a && b; a = *++str1, b = *++str2)
  {
    if (a == b) continue;
    else if (a > b) return 1;
    else if (a < b) return -1;
  }

  if (*str1) return 1;
  if (*str2) return -1;
  return 0;
}

int main()
{
  std::cout<<strlen("Hello")<<"\n";
  std::cout<<strlen("")<<"\n";
  std::cout<<strlen("Hello\0df")<<"\n";

  char copy[10];
  std::cout<<strcpy("hello", copy)<<"\n";
  std::cout<<copy<<"\n";

  std::cout<<strcmp("hello", "vello")<<"\n";
  std::cout<<strcmp("vello", "hello")<<"\n";
  std::cout<<strcmp("hello", "hello")<<"\n";
  std::cout<<strcmp("helload", "hello")<<"\n";
  std::cout<<strcmp("vello", "vellodf")<<"\n";
  std::cout<<strcmp("", "v")<<"\n";
  return 0;
}