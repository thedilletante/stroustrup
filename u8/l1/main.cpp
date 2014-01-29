#include <iostream>
#include <string>
#include <algorithm>

#define EVER ;;

namespace Stack {
	void push(const std::string&);
	std::string pop();

	void sort();
	void reverse();

	class Overflow {};
	class Underflow {};
}

void init() {
	Stack::push("Python");
	Stack::push("C++");
	Stack::push("PHP");
}

void printAll() {
	try {
		for(EVER) 
			std::cout << Stack::pop() << std::endl;
	}
	catch (Stack::Underflow& ex) {
		std::cout << "stop" << std::endl;
	}
}

int main() {
	init();
	printAll();
	init();
	Stack::sort();
	printAll();
	return 0;
}

namespace Stack {
	const int max_size = 200;
	std::string v[max_size];
	int top = 0;

	void push(const std::string& s) {
		if (top == max_size) throw Overflow();
		v[top] = s;
		++top;
	}

	std::string pop() {
		if (top == 0) throw Underflow();
		return v[--top];
	}

	void sort() {
		std::sort(v, v + top);
	}

	void reverse() {
		std::reverse(v, v + top);
	}
}