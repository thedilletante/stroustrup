#include <iostream>
#include <limits>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <cstring>

#define GET_NAME(STR) #STR

template <typename T>
struct RealType;

struct Type {
  const char * name;

  Type(const char * n) : name(n) {}
  virtual ~Type() {}

  virtual void print(bool only_name = true) {
    std::cout<<name;
  }

  virtual long double getMin() const = 0;
  virtual long double getMax() const = 0;
};

typedef std::vector<Type *> typeContainer_t;

void fillArray(typeContainer_t * a);
void freeArray(typeContainer_t * a);
void printArray(const typeContainer_t & a, bool only_name = true);

bool cmpByMin(const Type * a, const Type * b) {
  return ( a->getMin() > b->getMin() );
}

bool cmpByMax(const Type * a, const Type * b) {
  return ( a->getMax() < b->getMax() );
}

bool cmpByName(const Type * a, const Type *b) {
  return ( strcmp(a->name, b->name) <= 0 );
}

bool customCmp(const Type * a, const Type * b) {
  if ( a->getMin() == 0 ) {
    if ( b->getMin() == 0 ) {
      return a->getMax() < b->getMax();
    }
    return true;
  }
  else if ( b->getMin() == 0) {
    return false;
  }
  if (a->getMin() < b->getMin() && a->getMax() > b->getMax()) {
    return false;
  }
  return true;
}

int main() {
  typeContainer_t a;

  fillArray(&a);
  std::sort(a.begin(), a.end(), customCmp);

  printArray(a, false);

  freeArray(&a);
  return 0;
}



template <typename T>
struct RealType : Type {
  T min;
  T max;

  RealType(const char * n, T _min, T _max) : Type(n), min(_min), max(_max) {}

  virtual void print(bool only_name = true) {
    Type::print();
    if (only_name == false) {
      std::cout<<": ("<<getMin()<<" : "<<getMax()<<")";
    }
  }

  virtual long double getMin() const {
    return (long double)min;
  }
  virtual long double getMax() const {
    return (long double)max;
  }
};

#define SPECIALIZE(TYPE) \
template <> \
struct RealType<TYPE> : Type { \
  TYPE min; \
  TYPE max; \
\
  RealType(const char * n, TYPE _min, TYPE _max) : Type(n), min(_min), max(_max) {} \
\
  virtual void print(bool only_name = true) { \
    Type::print(); \
    if (only_name == false) { \
      std::cout<<": ("<<-getMax()<<" : "<<getMax()<<")"; \
    } \
  } \
\
  virtual long double getMin() const { \
    return (long double)-max; \
  } \
  virtual long double getMax() const { \
    return (long double)max; \
  } \
} 

SPECIALIZE(float);
SPECIALIZE(double);
SPECIALIZE(long double);

void fillArray(typeContainer_t * a) {

#define PUSH_TYPE(TYPE, VECTOR, STRUCT) \
    VECTOR->push_back(new STRUCT<TYPE>(#TYPE, std::numeric_limits<TYPE>::min(), std::numeric_limits<TYPE>::max()))
#define PUSH(TYPE, VECTOR) PUSH_TYPE(TYPE, VECTOR, RealType)
#define INSERT(TYPE) PUSH(TYPE, a)
    
  INSERT(char);
  INSERT(unsigned char);
  INSERT(signed char);

  INSERT(bool);

  INSERT(short);
  INSERT(unsigned short);
  INSERT(signed short);

  INSERT(int);
  INSERT(unsigned int);

  INSERT(long);
  INSERT(unsigned long);
  INSERT(signed long);

  INSERT(float);
  INSERT(double);
  INSERT(long double);
}


void freeArray(typeContainer_t * a) {
  for (size_t cur = 0, length = a->size(); cur < length; ++cur) {
    delete a->at(cur);
  }
}

void printArray(const typeContainer_t & a, bool only_name) {
  for (size_t cur = 0, length = a.size(); cur < length; ++cur) {
    a.at(cur)->print(only_name);
    std::cout<<"\n";
  }
}