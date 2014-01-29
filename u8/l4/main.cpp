#include <iostream>

void thrower() {
	throw std::exception();
}

void catcher() {
	try {
		thrower();
	}
	catch(std::exception& e) {
		std::cout << "exception with message:\n"<< e.what() << std::endl;
	}
}

int main() {
	catcher();
	return 0;
}