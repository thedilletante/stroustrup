#include <string>
#include <complex>

struct Date;
int day (Date * p);
template<class T>T abs(T a);
int error_number;

enum Beer { Carlsberg, Tuborg, Thor };
namespace NS { int a; }
using namespace NS;
enum Beer;

int main()
{
	char ch; // extert char ch;
	std::string s; // extert std::string s;
	int count = 1; // extern int count;
	const double pi = 3.1415926535897932385; // extern const double pi;
	extern int error_number;
	const char * name = "Njal"; // extern const char * name;
	const char * season[] = { "spring", "summer", "fall", "winter" }; // extern const char * season[];

	double sqrt(double);

	typedef std::complex<short> Point;
	struct User;
}

struct Date	{ int d, m, y; };
int day (Date * p) { return p->d; }
double sqrt(double a){
	return a*a;
}
template<class T>T abs(T a) { return a<0 ? -a : a; }
struct User {
	std::string fio;
};