/*
Определите два класса, каждый со статическим членом, так,
чтобы конструирование статического члена использовало ссылку
на другой статический член. Где такое может встретиться
в реальном коде? Как нужно модифицировать эти классы, чтобы
устранить в конструкторах зависимость от порядка?
*/

#include <iostream>

class Member
{
public:
	Member() { std::cout << "Member::Member()\n"; }
	Member(const Member &copy) { std::cout << "Member::Member(const Member &copy)\n"; }
	Member &operator=(const Member &copy) { std::cout << "Member::Member &operator=(const Member &copy)\n"; return *this; }
};

class First
{
public:
	static Member a;
};

class Second
{
public:
	static Member a;
};

Member First::a = Second::a;
Member Second::a = First::a;

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}