#include <iostream>
#include <fstream>
#include <ctime>

int main() {
	clock_t t_100_files_start;
	clock_t t_100_files_end;
	clock_t t_one_file_start;
	clock_t t_one_file_end;
	char ch;

	t_100_files_start = clock();
	for (unsigned i = 0; i < 100; ++i) {
		std::ifstream file("1500");
		while(file.get(ch)) std::cout << ch;
	}
	t_100_files_end = clock();

	t_one_file_start = clock();
	{
		std::ifstream file("150000");
		while(file.get(ch)) std::cout << ch;
	}
	t_one_file_end = clock();

	std::cout << "\n\ndiff is " << ((t_100_files_end - t_100_files_start) - (t_one_file_end - t_one_file_start)) << "\n";

	return 0;
}