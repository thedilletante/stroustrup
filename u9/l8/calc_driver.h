#ifndef CALC_DRIVER
#define CALC_DRIVER

#include <iostream>
#include "lexer.h"
#include "parser.h"

namespace Driver {

  extern std::istream * input;
  extern unsigned line_number;

  int calculate(std::istream* is = &std::cin, std::ostream* os = &std::cout);
  void skip();
}


namespace Error {

  extern int no_of_errors;

  struct Zero_divide {
    Zero_divide() { ++no_of_errors; }
  };

  struct Syntax_error {
    const char* p;
    Syntax_error(const char* q) : p(q) { ++no_of_errors; }
    Syntax_error(const std::string& q) : p(q.c_str()) { ++no_of_errors; }
  };
}




#endif // CALC_DRIVER