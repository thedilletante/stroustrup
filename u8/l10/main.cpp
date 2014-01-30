#include <iostream>
#include <sstream>
#include <limits>

class overflow {};
class loss_of_accuracy {};


double plus(double a, double b) {
	bool positive_a = (a > 0) ? true : false;
	bool positive_b = (b > 0) ? true : false;
	if (!(positive_a ^ positive_b)) {
		double limit = std::numeric_limits<double>::max();
		double _a = (positive_a) ? a : -a;
		double _b = (positive_b) ? b : -b;
		if (_a > limit - _b) throw overflow();
	}
	return a + b;
}

double minus(double a, double b) {
	return plus(a, -b);
}

double multiply(double a, double b) {
	double result = a * b;
	if (result / a != b) throw loss_of_accuracy();
	return result;
}

double divide(double a, double b) {
	double result = a / b;
	if (result * b != a) throw loss_of_accuracy();
	return a / b;
}

int main(int argc, char* argv[]) {\
	if (argc == 3) {
		double a,b;
		std::stringstream first(argv[1]), second(argv[2]);
		first >> a;
		second >> b;
		std::cout << "Numbers: " << a << " " << b << std::endl;
		std::cout << "plus    : " << plus(a, b) << std::endl;
		std::cout << "minus   : " << minus(a, b) << std::endl;
		std::cout << "multiply: " << multiply(a, b) << std::endl;
		std::cout << "divide  : " << divide(a, b) << std::endl;
	}
	return 0;
}