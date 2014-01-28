#include <iostream>

#define SHOW_SIZE(TYPE) std::cout<<"Size of type: "#TYPE" is "<<sizeof(TYPE)<<'\n';

enum Bool {FALSE, TRUE};
enum Days {Sunday, Monday, Tuesday, Wednesday, Thusday, Friday, Satuday};
enum Month {
	December = 12, January = 1, February,
	March, April, May,
	June, July, August, 
	September, October, November
};
enum BigInterval {One = -4564646464645646465, Two = 6546654656564};

int main() {
	SHOW_SIZE(char);
	SHOW_SIZE(unsigned char);
	SHOW_SIZE(signed char);
	SHOW_SIZE(bool);
	SHOW_SIZE(short);
	SHOW_SIZE(unsigned short);
	SHOW_SIZE(signed short);
	SHOW_SIZE(int);
	SHOW_SIZE(unsigned int);
	SHOW_SIZE(long);
	SHOW_SIZE(unsigned long);
	SHOW_SIZE(signed long);

	SHOW_SIZE(float);
	SHOW_SIZE(double);
	SHOW_SIZE(long double);

	SHOW_SIZE(Bool);
	SHOW_SIZE(Days);
	SHOW_SIZE(Month);
	SHOW_SIZE(BigInterval);
	return 0;
}