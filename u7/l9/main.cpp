#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "usage: " << argv[0] << " keyword" << std::endl;
	}
	else {
		std::string keyword(argv[1]);
		size_t len = keyword.length();
		char ch = 0;
		for (int counter = 0; std::cin.get(ch); ++counter) {
			ch ^= keyword.at( counter % len );
			std::cout << ch;
		}
	}
	return 0;
}