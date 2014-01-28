#include <iostream>

void ch_codes(char from, char to) {
	for (char ch = from; ch <= to; ++ch) {
		std::cout << std::hex << (int)ch 
			<< std::dec << ' ' << (int)ch
			<< ' ' << ch << '\n';
	}
}

int main() {
	ch_codes('1' - 10, 'z');
	return 0;
}