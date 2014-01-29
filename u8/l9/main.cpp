#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include <vector>
#include <cmath>


namespace Calculator {
  enum Token_value {
    NAME,         NUMBER,       END,
    PLUS = '+',   MINUS = '-',  MUL = '*',    DIV = '/',
    PRINT = ';',  ASSIGN = '=', LP = '(',     RP = ')',
    ARG_SEP = ',',
  };

  std::istream * input;
  int no_of_errors;
  unsigned line_number;
  std::map<std::string, double> table;
  Token_value curr_tok = PRINT;

  typedef std::pair<std::vector<std::string>, std::string> user_func_t;
  std::map<std::string, user_func_t> user_funcs;

  typedef double (*sys_func_t)(double);
  std::map<std::string, sys_func_t> sys_func;

  double expr(bool get);
  double term(bool get);
  double prim(bool get);
  double function();
  bool set_args(std::string& buf);
  bool parse_args(size_t args_count, std::vector<double>& fact_args);
  double def_func(const std::string& name, const std::string& args);
  double call_user_func(const std::string& name, const std::string& args);
  double call_sys_func(const std::string& name, const std::string& args);

  Token_value get_token();

  double error(const char * s);

  struct value_s {
    double number_value;
    std::string string_value;
  };

  value_s cur_val;
}

int main(int argc, char* argv[]) {
  switch(argc) {
    case 1:
      Calculator::input = &std::cin;
      break;
    case 2:
      Calculator::line_number = 1;
      Calculator::input = new std::istringstream(argv[1]);
      break;
    default:
      Calculator::error("too many arguments");
      return 1;
  }

  Calculator::table["pi"] = 3.1415926535897932385;
  Calculator::table["e"] = 2.7182818284590452354;

  Calculator::sys_func["sqrt"] = sqrt;
  Calculator::sys_func["log"] = log;
  Calculator::sys_func["sin"] = sin;

  while(*Calculator::input) {
    Calculator::get_token();
    if (Calculator::curr_tok == Calculator::END) break;
    if (Calculator::curr_tok == Calculator::NAME 
        && Calculator::cur_val.string_value == "exit") break;
    if (Calculator::curr_tok == Calculator::PRINT) continue;
    std::cout<<Calculator::expr(false)<<'\n';
  }

  if (Calculator::input != &std::cin) delete Calculator::input;

  return Calculator::no_of_errors;
}

double Calculator::expr(bool get) {
  double left = term(get);
  for( ;; ) {
    switch(curr_tok) {
      case PLUS: left += term(true); break;
      case MINUS: left -= term(true); break;
      default: return left;
    }
  }
}

double Calculator::term(bool get) {
  double left = prim(get);
  for( ;; ) {
    switch(curr_tok) {
      case MUL: left *= prim(true); break;
      case DIV:
        if (double d = prim(true)) {
          left /= d;
          break;
        }
        return error("divide by 0");
      default: return left;
    }
  }
}

double Calculator::prim(bool get) {
  if (get) get_token();
  switch(curr_tok) {
    case NUMBER: {
      double v = cur_val.number_value;
      get_token();
      return v;
    }
    case NAME: {
      double v;
      switch(get_token()) {
        case LP:
          v = function();
          break;
        case ASSIGN:
          table[cur_val.string_value] = expr(true);
        default:
          v = table[cur_val.string_value];
          break;
      }
      return v;
    }
    case MINUS: return -prim(true);
    case LP: {
      double e = expr(true);
      if (curr_tok != RP) return error("')' expected");
      get_token();
      return e;
    }
    default: return error("primary expected");
  }
}

double Calculator::function() {
  std::string name = cur_val.string_value;
  std::string args;
  if (set_args(args)) {
	  double result;
	  Token_value tmp;
	  switch (tmp = get_token()) {
	  	case ASSIGN:
	  		result = def_func(name, args);
	  		curr_tok = PRINT;
	  		break;
	  	default:
        if (user_funcs.find( name ) != user_funcs.end()) {
          result = call_user_func(name, args);
        }
        else if (sys_func.find( name ) != sys_func.end()) {
          result = call_sys_func(name, args);
        }
        else {
          result = error("function can't finded");
        }
	  		curr_tok = tmp;
	  		break;
	  }
	  return result;
  }
  else
  	return error("");
}

bool Calculator::set_args(std::string& buf){
	char ch;
	unsigned cnt = 1;
	while(input->get(ch)) {
		switch (ch) {
			case LP:
				++cnt;
				break;
			case RP:
				--cnt;
				break;
			case PRINT:
				error("RP expected");
				return false;
		}
		if (cnt == 0)
			break;
		buf.push_back(ch);
	}
	if (!ch) {
		error("argument list expected");
		return false;
	}
	return true;
}

double Calculator::def_func(const std::string& name, const std::string& args) {
	std::vector<std::string> arg_list;
	std::string body;
	std::string msg;

	std::istream * arguments = new std::stringstream(args);
	std::istream * tmp = input;
	input = arguments;

	while(*input) {
		if (get_token() != NAME) {
			msg = "arguments must be a string value";
			break;
		}
		arg_list.push_back(cur_val.string_value);
		Token_value v = get_token();
		if (v != ARG_SEP && v != END) {
			msg = "arguments must devides by comma";
			break;
		}
	}

	input = tmp;
	delete arguments;

	if (msg.empty()) {
		char ch;
		while(input->get(ch) && (ch != PRINT && ch != '\n')) {
			body.push_back(ch);
		}

		if (body.empty()) {
			msg = "body is empty";
		}
		else {
			user_funcs[name] = user_func_t( arg_list, body );
			msg = "function " + name + "() is defined";
		}
	}

	return error(msg.c_str());
}

double Calculator::call_user_func(const std::string& func_name, const std::string& fact_args) {
  user_func_t function = user_funcs[ func_name ];

  std::vector<std::string> args = function.first;
  std::istream * body = new std::stringstream(function.second);
  std::istream * arg_list = new std::stringstream(fact_args);

  std::map<std::string, double> tmp_table = table;

  std::istream * tmp_input = input;
  input = arg_list;
  curr_tok = END;
  std::vector<double> arguments;
  double result = 0;
  if (parse_args(args.size(), arguments)) {
    for (size_t i = 0, size = args.size(); i < size; ++i) {
      table[ args.at(i) ] = arguments.at(i);
    }
    input = body;
    result = expr(true);
  }
  input = tmp_input;
  table = tmp_table;
  delete arg_list;
  delete body;

  return result;
}

bool Calculator::parse_args(size_t args_count, std::vector<double>& fact_args) {
  size_t counter = 0;
  while (*input) {
    if (curr_tok == PRINT) {
      error(") expected");
      return false;
    }
    if (args_count < counter + 1) {
      std::string message = "too many arguments to call function";
      error(message.c_str());
      return false;
    }
    fact_args.push_back(expr(true));
    if (curr_tok != ARG_SEP && curr_tok != END) {
      error("unknown error");
      return false;
    }
    ++counter;
  }
  if (counter != args_count) {
    std::string message = "too small arguments to call function";
    error(message.c_str());
    return false;
  }
  return true;
}

double Calculator::call_sys_func(const std::string& name, const std::string& fact_args) {
  sys_func_t func = sys_func[ name ];
  std::istream * args = new std::istringstream(fact_args);
  std::istream * tmp = input;
  input = args;
  curr_tok = END;
  std::vector<double> arguments;
  double result = 0;
  if (parse_args(1, arguments)) {
    result = func(arguments.at(0));
  }
  input = tmp;
  delete args;
  return result;
}

Calculator::Token_value Calculator::get_token() {
  char ch;
  do {
    if (!input->get(ch)) return curr_tok = END;
  } while(ch != '\n' && isspace(ch));

  switch(ch) {
    case PRINT: case '\n': ++line_number; return curr_tok = PRINT;
    case PLUS: case MINUS: case MUL: case DIV: case LP: case RP: case ASSIGN: case ARG_SEP:
      return curr_tok = Token_value(ch);
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
      input->putback(ch);
      *input>>cur_val.number_value;
      return curr_tok = NUMBER;
    default:
      if (isalpha(ch)) {
        cur_val.string_value = ch;
        while(input->get(ch) && isalnum(ch)) cur_val.string_value.push_back(ch);
        input->putback(ch);
        return curr_tok = NAME;
      }
      error("bad token");
      return curr_tok = PRINT;
  }
}

double Calculator::error(const char * s) {
  ++no_of_errors;
  std::cerr<<"error at line["<<line_number<<"]: "<<s<<'\n';
  return 1;
}
