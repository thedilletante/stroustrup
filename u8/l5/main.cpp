#include <iostream>
#include <sstream>

void ping(size_t);
void pong(size_t);

class Ex {
public:
	Ex(size_t l) : level(l) {}
	size_t level;
};

size_t exception_level = 1;
const size_t MAX_LEVEL = 10;

int main(int argc, char* argv[]) {
	if (argc == 2) {
		std::stringstream lvl_str(argv[1]);
		size_t lvl;
		lvl_str >> lvl;
		if (0 < lvl == lvl < MAX_LEVEL) exception_level = lvl;
	}
	try {
		ping(0);
	}
	catch(Ex& e) {
		std::cout << "exception throwed with level: " << e.level << std::endl;
	}
	return 0;
}


void ping(size_t level) {
	if (level == MAX_LEVEL) return;
	if (level == exception_level) throw Ex(level);
	pong(level + 1);
}

void pong(size_t level) {
	try {
		if (level == MAX_LEVEL) return;
		if (level == exception_level) throw Ex(level);
	}
	catch (Ex& e) {
		std::cout << "pong catch the exception with level " << e.level << std::endl;
	}
	ping(level + 1);
}