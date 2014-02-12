#include <iostream>
#include "intset.h"

int main() {
	Intset a;
	Intset b;

	a.insert(1).insert(2).insert(3).insert(4);
	b.insert(2).insert(4).insert(5).insert(10);

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	
	std::cout << (a += b) << std::endl;
	std::cout << (a *= b) << std::endl;
	std::cout << (a -= b) << std::endl;

	return 0;
}