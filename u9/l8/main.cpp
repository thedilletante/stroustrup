/*
Модифицируте нашу версию калькулятора так, чтобы его можно было вызвать
из main(), либо из любой другой функции (в виде обычного функционального
вызова).
*/

#include <iostream>
#include <sstream>
#include <cmath>

#include "calc_driver.h"
#include "lexer.h"

int main(int argc, char* argv[]) {

  Lexer::table["pi"] = 3.1415926535897932385;
  Lexer::table["e"] = 2.7182818284590452354;

  Lexer::sys_func["sqrt"] = sqrt;
  Lexer::sys_func["log"] = log;
  Lexer::sys_func["sin"] = sin;

  switch(argc) {
    case 1:
      return Driver::calculate();
      break;
    case 2: {
      std::istream * input = new std::istringstream(argv[1]);
      int result = Driver::calculate(input);
      delete input;
      return result;
    }
      break;
    default:
      std::cerr << "too many arguments\n";
      return 1;
  }
}





