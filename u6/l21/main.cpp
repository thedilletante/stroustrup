#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include <vector>

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

std::map<std::string, double> table;

typedef std::pair<std::vector<std::string>, std::string> user_func_t;
std::map<std::string, user_func_t> user_funcs;

int no_of_errors;
unsigned line_number;

std::istream * input;

double expr(bool get);
double term(bool get);
double prim(bool get);
double function();
bool set_args(std::string& buf);
double def_func(const std::string& name, const std::string& args);
double call_func(const std::string& name, const std::string& args);

Token_value get_token();

double error(const char * s);

#define ADD_FUNC_0(name, body) \
  {\
    user_funcs[#name] = user_func_t(std::vector<std::string>(), #body); \
  }

#define ADD_FUNC_1(name, arg, body) \
  {\
    std::vector<std::string> args_for_##name; \
    args_for_##name.push_back(#arg); \
    user_funcs[#name] = user_func_t(args_for_##name, #body); \
  }

#define ADD_FUNC_2(name, arg1, arg2, body) \
  {\
    std::vector<std::string> args_for_##name; \
    args_for_##name.push_back(#arg1); \
    args_for_##name.push_back(#arg2); \
    user_funcs[#name] = user_func_t(args_for_##name, #body); \
  }

#define ADD_FUNC_3(name, arg1, arg2, arg3, body) \
  {\
    std::vector<std::string> args_for_##name; \
    args_for_##name.push_back(#arg1); \
    args_for_##name.push_back(#arg2); \
    args_for_##name.push_back(#arg3); \
    user_funcs[#name] = user_func_t(args_for_##name, #body); \
  }

int main(int argc, char* argv[]) {
  switch(argc) {
    case 1:
      input = &std::cin;
      break;
    case 2:
      line_number = 1;
      input = new std::istringstream(argv[1]);
      break;
    default:
      error("too many arguments");
      return 1;
  }

  table["pi"] = 3.1415926535897932385;
  table["e"] = 2.7182818284590452354;

  /*ADD_FUNC_1(incr, x, x+1);
  ADD_FUNC_2(summ, x, y, x + y);
  ADD_FUNC_1(quad, x, x*x);
  ADD_FUNC_1(cube, x, x*x*x);
  ADD_FUNC_3(f, x, y, z, x*y-z);
*/
  while(*input) {
    get_token();
    if (curr_tok == END) break;
    if (curr_tok == PRINT) continue;
    std::cout<<expr(false)<<'\n';
  }

  if (input != &std::cin) delete input;

  return no_of_errors;
}


double expr(bool get) {
  double left = term(get);
  for( ;; ) {
    switch(curr_tok) {
      case PLUS: left += term(true); break;
      case MINUS: left -= term(true); break;
      default: return left;
    }
  }
}

double term(bool get) {
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

double prim(bool get) {
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

double function() {
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
	  		result = call_func(name, args);
	  		curr_tok = tmp;
	  		break;
	  }
	  return result;
  }
  else
  	return error("");
}

bool set_args(std::string& buf){
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

double def_func(const std::string& name, const std::string& args) {
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

double call_func(const std::string& func_name, const std::string& fact_args) {
  if ( user_funcs.find( func_name ) == user_funcs.end() ) {
    std::string message = "function " + func_name + "()" + " is not defined";
    return error(message.c_str());
  }
  user_func_t function = user_funcs[ func_name ];

  std::vector<std::string> args = function.first;
  std::istream * body = new std::stringstream(function.second);
  std::istream * arg_list = new std::stringstream(fact_args);

  std::map<std::string, double> tmp_table = table;

  unsigned counter = 0;
  unsigned args_count = args.size();

  std::istream * tmp_input = input;
  input = arg_list;
  curr_tok = END;
  while (*input) {
    if (curr_tok == PRINT) {
      return error(") expected");
    }
    if (args_count < counter + 1) {
      std::string message = "too many arguments to call function " + func_name + "()";
      return error(message.c_str());
    }
    double v = expr(true);
    table[ args[counter] ] = v;
    if (curr_tok != ARG_SEP && curr_tok != END) {
      return error("unknown error");
    }
    ++counter;
  }
  input = tmp_input;
  delete arg_list;

  if (counter != args_count) {
    std::string message = "too small arguments to call function " + func_name + "()";
    return error(message.c_str());
  }

  input = body;

  double result = expr(true);

  table = tmp_table;
  input = tmp_input;
  delete body;

  return result;
}

Token_value get_token() {
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

double error(const char * s) {
  ++no_of_errors;
  std::cerr<<"error at line["<<line_number<<"]: "<<s<<'\n';
  return 1;
}
