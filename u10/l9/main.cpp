#include <iostream>
#include <cstdlib>
#include <cstring>
#include "intset.h"

int main(int argc, char *argv[]) {
	Intset a;
	Intset b;

    int tmp;
    for (int i = 1; i < argc; ++i)
    {
        if (strlen(argv[i]) > 1)
        {
            tmp = atoi(&argv[i][1]);
            switch(argv[i][0])
            {
                case 'A': a.insert(tmp); break;
                case 'B': b.insert(tmp); break;
            }
        }
    }

    std::cout << "A:" << std::endl;
	std::cout << a << std::endl;
    std::cout << "B:" << std::endl;
	std::cout << b << std::endl;
	
    std::cout << "A + B" << std::endl;
	std::cout << (a + b) << std::endl;
    std::cout << "A * B" << std::endl;
	std::cout << (a * b) << std::endl;
    std::cout << "A - B" << std::endl;
	std::cout << (a - b) << std::endl;
    std::cout << "B - A" << std::endl;
    std::cout << (b - a) << std::endl;

	return 0;
}
