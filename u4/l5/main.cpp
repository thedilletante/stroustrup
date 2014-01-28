#include <iostream>
#include <limits>

#define SHOW_RANGE(TYPE) \
	std::cout<<std::numeric_limits<TYPE>::min() \
	<< "\t<=\t"#TYPE"\t<=\t" \
	<<std::numeric_limits<TYPE>::max()<<'\n';

int main() {
	SHOW_RANGE(char);
	SHOW_RANGE(unsigned char);
	SHOW_RANGE(signed char);
	SHOW_RANGE(bool);
	SHOW_RANGE(short);
	SHOW_RANGE(unsigned short);
	SHOW_RANGE(signed short);
	SHOW_RANGE(int);
	SHOW_RANGE(unsigned int);
	SHOW_RANGE(long);
	SHOW_RANGE(unsigned long);
	SHOW_RANGE(signed long);

	SHOW_RANGE(float);
	SHOW_RANGE(double);
	SHOW_RANGE(long double);
	return 0;
}