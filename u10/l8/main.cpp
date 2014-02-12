#include <iostream>
#include "ttree.h"

int main() {
	std::vector<std::string> a;

	a.push_back("C++");
	a.push_back("Assembler");
	a.push_back("Basic");
	a.push_back("PHP");
	a.push_back("Ruby");
	a.push_back("Ada");
	a.push_back("C#");

	Ttree t(a);
	std::cout << t << std::endl;
	return 0;
}