#include "calc_driver.h"

std::istream * Driver::input = 0;
unsigned Driver::line_number = 1;

int Error::no_of_errors = 0;

int Driver::calculate(std::istream* is, std::ostream* os) {
  input = is;
  line_number = 0;
  Error::no_of_errors = 0;
  while(input) {
    try {
      Lexer::get_token();
      if (Lexer::curr_tok == Lexer::END) break;
      if (Lexer::curr_tok == Lexer::NAME 
          && Lexer::cur_val.string_value == "quit") break;
      if (Lexer::curr_tok == Lexer::PRINT) continue;
      *os << Parser::expr(false) << '\n';
    }
    catch (Error::Zero_divide&) {
      std::cerr << "attempt to divide by zero\n";
      if (Lexer::curr_tok != Lexer::PRINT) skip();
    }
    catch (Error::Syntax_error& e) {
      std::cerr << "syntax error [" << line_number << "]: " << e.p << "\n";
      if (Lexer::curr_tok != Lexer::PRINT) skip();
    }
    catch (Lexer::Function_notify& e) {
      std::cerr << e.p << "\n";
      if (Lexer::curr_tok != Lexer::PRINT) skip();
    }
    catch (Ariphmetic::overflow&) {
      std::cerr << "overflow on line [" << line_number << "]\n";
      if (Lexer::curr_tok != Lexer::PRINT) skip();
    }
    catch (Ariphmetic::loss_of_accuracy&) {
      std::cerr << "loss of occuracy on line [" << line_number << "]\n";
      if (Lexer::curr_tok != Lexer::PRINT) skip();
    }
    ++Driver::line_number;
  }

  return Error::no_of_errors;
}

void Driver::skip() {
  char ch;
  while(*input) {
    input->get(ch);
    switch(ch) {
      case '\n': case ';':
        return;
    }
  }
}