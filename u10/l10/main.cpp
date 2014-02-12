#include <iostream>
#include "intset.h"

int main() {
	Intset a;
	Intset b;

	a.insert(Node("hello")).insert(Node("bye")).insert(Node("one"));
	b.insert(Node("bye")).insert(Node("some")).insert(Node("hello"));

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	
	std::cout << a + b << std::endl;
	std::cout << a * b << std::endl;
	std::cout << a - b << std::endl;
	std::cout << b - a << std::endl;

	return 0;
}