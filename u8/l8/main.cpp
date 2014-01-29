#include <iostream>
#include <ctime>

class Ex {
public:
	Ex(int v) : value(v) {}
private:
	int value;
};


int f(bool isThrow) {
	if (isThrow) throw Ex(0);
	return 0;
}

int main() {
	clock_t ret_s, ret_e, thr_s, thr_e;

	ret_s = clock();
	f(false);
	ret_e = clock();

	try {
		thr_s = clock();
		f(true);
	}
	catch(Ex& e) {
		thr_e = clock();
	}

	clock_t ret = ret_e - ret_s;
	clock_t thr = thr_e - thr_s;

	std::cout << "diff is " << ret - thr << std::endl;
	std::cout << "in seconds " << ((float)(ret - thr))/CLOCKS_PER_SEC << std::endl;
	return 0;
}