#ifndef CALC_PARSER
#define CALC_PARSER

#include <iostream>
#include <sstream>
#include "lexer.h"
#include "ariphmetic.h"
#include "calc_driver.h"

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

  template<class T> // to automatic restore original value after exit from scope
  class Restorer {
  public:
  	Restorer(T& obj) : origin(obj), tmp(obj) {}
  	~Restorer() { origin = tmp; }
  	void restore() { origin = tmp; }
  private:
  	T& origin;
  	T tmp;
  };

  template<class T> // for auto delete objects after exit from scope
  class Auto_ptr {
  public:
  	Auto_ptr(T* val) : obj(val) {}
  	T* val() { return obj; }
  	~Auto_ptr() { delete obj; } 
  private:
  	T* obj;
  };
}

#endif // CALC_PARSER