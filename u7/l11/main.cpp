#include <cstdarg>
#include <iostream>

void error(const char * format ... ) {
  va_list ap;
  va_start( ap, format );

  char ch = 0;
  bool spec = false;
  while( ch = *format ) {
    if (ch == '%') {
      ++format;
      if ( ch = *format ) {
        switch (ch) {
          case 'd': {
            int p = va_arg( ap, int );
            std::cout<<p;
          }
          break;
          case 'c': {
            char p = va_arg( ap, int );
            std::cout<<p;
          }
          break;
          case 's': {
            char * p = va_arg( ap, char * );
            std::cout<<p;
          }
          break;
          default:
            std::cout<<ch;
        }
      }
      else
        break;
    }
    else
      std::cout<<ch;
    ++format;
  }
  va_end( ap );
}

int main() {
  error("hello, %s!\nThe symbol %% is %c with int %d\n", "Mikle", '%', 23);
  return 0;
}