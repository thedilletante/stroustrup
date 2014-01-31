#include "parser.h"

double Parser::expr(bool get) {
  double left = term(get);
  for( ;; ) {
    switch(Lexer::curr_tok) {
      case Lexer::PLUS: left = Ariphmetic::plus(left, term(true)); break;
      case Lexer::MINUS: left = Ariphmetic::minus(left, term(true)); break;
      default: return left;
    }
  }
}

double Parser::term(bool get) {
  double left = prim(get);
  for( ;; ) {
    switch(Lexer::curr_tok) {
      case Lexer::MUL: left = Ariphmetic::multiply(left, prim(true)); break;
      case Lexer::DIV:
        if (double d = prim(true)) {
          left = Ariphmetic::divide(left, d);
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
  double result = 0.0;
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
				throw Error::Syntax_error(") expected");
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

	Auto_ptr<std::istream> arguments(new std::stringstream(args));
	Restorer<std::istream*> rest(Driver::input);
	Driver::input = arguments.val();

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

	rest.restore();
  	char ch;
	while(Driver::input->get(ch) && (ch != Lexer::PRINT && ch != '\n')) {
		body.push_back(ch);
	}
	Lexer::curr_tok = Lexer::PRINT;

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
  Auto_ptr<std::istream> body(new std::stringstream(function.second));
  Auto_ptr<std::istream> arg_list(new std::stringstream(fact_args));
  Restorer<std::istream*> rest(Driver::input);
  Restorer<std::map<std::string, double> > table_rest(Lexer::table);

  Driver::input = arg_list.val();
  Lexer::curr_tok = Lexer::END;
  std::vector<double> arguments;
  double result = 0;
  parse_args(args.size(), arguments);
  for (size_t i = 0, size = args.size(); i < size; ++i) {
    Lexer::table[ args.at(i) ] = arguments.at(i);
  }
  Driver::input = body.val();
  result = expr(true);

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
  Auto_ptr<std::istream> args(new std::istringstream(fact_args));
  Restorer<std::istream*> rest(Driver::input);
  Driver::input = args.val();
  Lexer::curr_tok = Lexer::END;
  std::vector<double> arguments;
  double result = 0;
  parse_args(1, arguments);
  result = func(arguments.at(0));
  return result;
}