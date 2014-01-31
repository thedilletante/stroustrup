#include "lexer.h"
#include "calc_driver.h"
#include <cctype>


Lexer::Token_value Lexer::curr_tok = Lexer::PRINT;
Lexer::value_s Lexer::cur_val;
std::map<std::string, double> Lexer::table; // defined variables
std::map<std::string, Lexer::user_func_t> Lexer::user_funcs; // user defined functions
std::map<std::string, Lexer::sys_func_t> Lexer::sys_func; // system functions

Lexer::Token_value Lexer::get_token() {
  char ch;
  do {
    if (!Driver::input->get(ch)) return curr_tok = END;
  } while(ch != '\n' && isspace(ch));

  switch(ch) {
    case PRINT: case '\n': return curr_tok = PRINT;
    case PLUS: case MINUS: case MUL: case DIV: case LP: case RP: case ASSIGN: case ARG_SEP:
      return curr_tok = Token_value(ch);
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
      Driver::input->putback(ch);
      *Driver::input>>cur_val.number_value;
      return curr_tok = NUMBER;
    default:
      if (isalpha(ch)) {
        cur_val.string_value = ch;
        while(Driver::input->get(ch) && isalnum(ch)) cur_val.string_value.push_back(ch);
        Driver::input->putback(ch);
        return curr_tok = NAME;
      }
      Error::Syntax_error("bad token");
      return curr_tok = PRINT;
  }
}


