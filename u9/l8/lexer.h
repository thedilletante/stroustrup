#ifndef CALC_LEXER
#define CALC_LEXER

#include <string>
#include <map>
#include <vector>

namespace Lexer {
  enum Token_value {
    NAME,         NUMBER,       END,
    PLUS = '+',   MINUS = '-',  MUL = '*',    DIV = '/',
    PRINT = ';',  ASSIGN = '=', LP = '(',     RP = ')',
    ARG_SEP = ',',
  };

  extern Token_value curr_tok;

  struct value_s {
    double number_value;
    std::string string_value;
  };

  extern value_s cur_val;

  extern std::map<std::string, double> table; // defined variables

  typedef std::pair<std::vector<std::string>, std::string> user_func_t;
  extern std::map<std::string, user_func_t> user_funcs; // user defined functions

  typedef double (*sys_func_t)(double);
  extern std::map<std::string, sys_func_t> sys_func; // system functions


  Token_value get_token();

  struct Function_notify {
    const char* p;
    Function_notify(const char* q) : p(q) { }
    Function_notify(const std::string& q) : p(q.c_str()) { }
  };
}


#endif // CALC_LEXER