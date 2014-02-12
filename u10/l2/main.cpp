#include <iostream>
#include "date.h"

int main() {
	Date::set_default(4, Date::February, 2014);

	Date a(4, Date::March, 2014);
	Date b;
	std::cout << diff(a, b) << std::endl;
	return 0;
}