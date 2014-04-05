/*
Дана программа:
#include <iostream>
int main()
{
	std::cout << "Hello, World!\n";
}
Модифицируйте ее так, чтобы она выводила
Initialize
Hello, World!
Clean up
Не вносите при этом никаких изменений в функцию main().
*/


#include <iostream>
int main()
{
	std::cout << "Hello, World!\n";
}




class _wrapper
{
public:
	_wrapper()
	{
		std::cout << "Initialize\n";
	}
	~_wrapper()
	{
		std::cout << "Clean up\n";
	}
} wrapper;