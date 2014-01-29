#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include <vector>
#include <cmath>




// TODO
// проверить вариант с определением функции - возвращается в неправильное состояние

namespace Parser {

  double expr(bool get);
  double term(bool get);
  double prim(bool get);
  double function();

  void def_func(const std::string& name, const std::string& args);
  double call_user_func(const std::string& name, const std::string& args);
  double call_sys_func(const std::string& name, const std::string& args);
  void set_args(std::string& buf);
  void parse_args(size_t args_count, std::vector<double>& fact_args);
}

namespace Lexer {
  enum Token_value {
    NAME,         NUMBER,       END,
    PLUS = '+',   MINUS = '-',  MUL = '*',    DIV = '/',
    PRINT = ';',  ASSIGN = '=', LP = '(',     RP = ')',
    ARG_SEP = ',',
  };

  Token_value curr_tok = PRINT;

  struct value_s {
    double number_value;
    std::string string_value;
  };

  value_s cur_val;

  std::map<std::string, double> table; // defined variables

  typedef std::pair<std::vector<std::string>, std::string> user_func_t;
  std::map<std::string, user_func_t> user_funcs; // user defined functions

  typedef double (*sys_func_t)(double);
  std::map<std::string, sys_func_t> sys_func; // system functions


  Token_value get_token();

  struct Function_notify {
    const char* p;
    Function_notify(const char* q) : p(q) { }
    Function_notify(const std::string& q) : p(q.c_str()) { }
  };
}

namespace Driver {

  std::istream * input;
  unsigned line_number;

  void skip();
}

namespace Error {
  int no_of_errors;

  struct Zero_divide {
    Zero_divide() { ++no_of_errors; }
  };

  struct Syntax_error {
    const char* p;
    Syntax_error(const char* q) : p(q) { ++no_of_errors; }
    Syntax_error(const std::string& q) : p(q.c_str()) { ++no_of_errors; }
  };
}


int main(int argc, char* argv[]) {
  switch(argc) {
    case 1:
      Driver::input = &std::cin;
      break;
    case 2:
      Driver::line_number = 1;
      Driver::input = new std::istringstream(argv[1]);
      break;
    default:
      std::cerr << "too many arguments\n";
      return 1;
  }

  Lexer::table["pi"] = 3.1415926535897932385;
  Lexer::table["e"] = 2.7182818284590452354;

  Lexer::sys_func["sqrt"] = sqrt;
  Lexer::sys_func["log"] = log;
  Lexer::sys_func["sin"] = sin;

  while(*Driver::input) {
    try {
      Lexer::get_token();
      if (Lexer::curr_tok == Lexer::END) break;
      if (Lexer::curr_tok == Lexer::NAME 
          && Lexer::cur_val.string_value == "exit") break;
      if (Lexer::curr_tok == Lexer::PRINT) continue;
      std::cout<<Parser::expr(false)<<'\n';
    }
    catch (Error::Zero_divide&) {
      std::cerr << "attempt to divide by zero\n";
      if (Lexer::curr_tok != Lexer::PRINT) Driver::skip();
    }
    catch (Error::Syntax_error& e) {
      std::cerr << "syntax error [" << Driver::line_number << "]: " << e.p << "\n";
      if (Lexer::curr_tok != Lexer::PRINT) Driver::skip();
    }
    catch (Lexer::Function_notify& e) {
      std::cerr << e.p << "\n";
      if (Lexer::curr_tok != Lexer::PRINT) Driver::skip();
    }
  }

  if (Driver::input != &std::cin) delete Driver::input;

  return Error::no_of_errors;
}

double Parser::expr(bool get) {
  double left = term(get);
  for( ;; ) {
    switch(Lexer::curr_tok) {
      case Lexer::PLUS: left += term(true); break;
      case Lexer::MINUS: left -= term(true); break;
      default: return left;
    }
  }
}

double Parser::term(bool get) {
  double left = prim(get);
  for( ;; ) {
    switch(Lexer::curr_tok) {
      case Lexer::MUL: left *= prim(true); break;
      case Lexer::DIV:
        if (double d = prim(true)) {
          left /= d;
          break;
        }
        throw Error::Zero_divide();
      default: return left;
    }
  }
}

double Parser::prim(bool get) {
  if (get) Lexer::get_token();

  switch(Lexer::curr_tok) {
    case Lexer::NUMBER: {
      double v = Lexer::cur_val.number_value;
      Lexer::get_token();
      return v;
    }
    case Lexer::NAME: {
      double v;
      switch(Lexer::get_token()) {
        case Lexer::LP:
          v = function();
          break;
        case Lexer::ASSIGN:
          Lexer::table[Lexer::cur_val.string_value] = expr(true);
        default:
          v = Lexer::table[Lexer::cur_val.string_value];
          break;
      }
      return v;
    }
    case Lexer::MINUS: return -prim(true);
    case Lexer::LP: {
      double e = expr(true);
      if (Lexer::curr_tok != Lexer::RP) throw Error::Syntax_error("')' expected");
      Lexer::get_token();
      return e;
    }
    default: throw Error::Syntax_error("primary expected");
  }
}

double Parser::function() {
  std::string name = Lexer::cur_val.string_value;
  std::string args;
  set_args(args);
  double result;
  Lexer::Token_value tmp;
  switch (tmp = Lexer::get_token()) {
  	case Lexer::ASSIGN:
  		def_func(name, args);
  		break;
  	default:
      if (Lexer::user_funcs.find( name ) != Lexer::user_funcs.end()) {
        result = call_user_func(name, args);
      }
      else if (Lexer::sys_func.find( name ) != Lexer::sys_func.end()) {
        result = call_sys_func(name, args);
      }
      else {
        throw Error::Syntax_error("function " + name + " not founded");
      }
  		Lexer::curr_tok = tmp;
  		break;
  }
  return result;
}

void Parser::set_args(std::string& buf){
	char ch;
	unsigned cnt = 1;
	while(Driver::input->get(ch)) {
		switch (ch) {
			case Lexer::LP:
				++cnt;
				break;
			case Lexer::RP:
				--cnt;
				break;
			case Lexer::PRINT:
				throw Error::Syntax_error("RP expected");
		}
		if (cnt == 0)
			break;
		buf.push_back(ch);
	}
	if (!ch) throw Error::Syntax_error("argument list expected");
}

void Parser::def_func(const std::string& name, const std::string& args) {
	std::vector<std::string> arg_list;
	std::string body;

	std::istream * arguments = new std::stringstream(args);
	std::istream * tmp = Driver::input;
	Driver::input = arguments;

	while(*Driver::input) {
		if (Lexer::get_token() != Lexer::NAME) {
      throw Error::Syntax_error("arguments must be a string value");
		}
		arg_list.push_back(Lexer::cur_val.string_value);
		Lexer::Token_value v = Lexer::get_token();
		if (v != Lexer::ARG_SEP && v != Lexer::END) {
      throw Error::Syntax_error("arguments must devides by comma");
		}
	}

	Driver::input = tmp;
	delete arguments;

  char ch;
	while(Driver::input->get(ch) && (ch != Lexer::PRINT && ch != '\n')) {
		body.push_back(ch);
	}

	if (body.empty()) {
		throw Error::Syntax_error("body of function empty");
	}
	else {
		Lexer::user_funcs[name] = Lexer::user_func_t( arg_list, body );
    throw Lexer::Function_notify("function " + name + " defined");
	}
}

double Parser::call_user_func(const std::string& func_name, const std::string& fact_args) {
  Lexer::user_func_t function = Lexer::user_funcs[ func_name ];

  std::vector<std::string> args = function.first;
  std::istream * body = new std::stringstream(function.second);
  std::istream * arg_list = new std::stringstream(fact_args);

  std::map<std::string, double> tmp_table = Lexer::table;

  std::istream * tmp_input = Driver::input;
  Driver::input = arg_list;
  Lexer::curr_tok = Lexer::END;
  std::vector<double> arguments;
  double result = 0;
  try {
    parse_args(args.size(), arguments);
  }
  catch (Error::Syntax_error& e) {
    Driver::input = tmp_input;
    Lexer::table = tmp_table;
    delete arg_list;
    delete body;
    throw e;
  }
  for (size_t i = 0, size = args.size(); i < size; ++i) {
    Lexer::table[ args.at(i) ] = arguments.at(i);
  }
  Driver::input = body;
  result = expr(true);
  Driver::input = tmp_input;
  Lexer::table = tmp_table;
  delete arg_list;
  delete body;

  return result;
}

void Parser::parse_args(size_t args_count, std::vector<double>& fact_args) {
  size_t counter = 0;
  while (*Driver::input) {
    if (Lexer::curr_tok == Lexer::PRINT) {
      throw Error::Syntax_error(") expected");
    }
    if (args_count < counter + 1) {
      throw Error::Syntax_error("too many arguments to call function");
    }
    fact_args.push_back(expr(true));
    if (Lexer::curr_tok != Lexer::ARG_SEP && Lexer::curr_tok != Lexer::END) {
      throw Error::Syntax_error("unknown error");
    }
    ++counter;
  }
  if (counter != args_count) {
    throw Error::Syntax_error("too small arguments to call function");
  }
}

double Parser::call_sys_func(const std::string& name, const std::string& fact_args) {
  Lexer::sys_func_t func = Lexer::sys_func[ name ];
  std::istream * args = new std::istringstream(fact_args);
  std::istream * tmp = Driver::input;
  Driver::input = args;
  Lexer::curr_tok = Lexer::END;
  std::vector<double> arguments;
  double result = 0;
  try {
    parse_args(1, arguments);
  }
  catch (Error::Syntax_error& e) {
    Driver::input = tmp;
    delete args;
    throw e;
  }
  result = func(arguments.at(0));
  Driver::input = tmp;
  delete args;
  return result;
}

Lexer::Token_value Lexer::get_token() {
  char ch;
  do {
    if (!Driver::input->get(ch)) return curr_tok = END;
  } while(ch != '\n' && isspace(ch));

  switch(ch) {
    case PRINT: case '\n': ++Driver::line_number; return curr_tok = PRINT;
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