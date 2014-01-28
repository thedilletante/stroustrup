#include <iostream>

struct Date {
  unsigned y, m, d;
};

bool leap(int year) {
	return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
}

void initDate(Date * date) {
  date->y = 2013;
  date->m = 10;
  date->d = 20;
}

void readDate(Date * date) {
  unsigned y, m, d;
  std::cout<<"Input year: ";
  std::cin>>y;
  std::cout<<"Input month: ";
  std::cin>>m;
  if (1 <= m == m <= 12) {
  	std::cout << "Input day: ";
  	std::cin >> d;
  	if (d > 0) {
  		int max = 0;
	  	switch (m) {
	  		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
	  			max = 31;
	  			break;
	  		case 2:
	  			max = 28 + leap(y);
	  			break;
	  		default:
	  			max = 30;
	  			break;
	  	}
	  	if (d <= max) {
	  		date->y = y;
	  		date->m = m;
	  		date->d = d;
	  		return;
	  	}
  	}
  }
  std::cout << "Unrecognized date" << std::endl;
}

void printDate(const Date & date) {
  std::cout<<date.d<<"."<<date.m<<"."<<date.y<<"\n";
}


int main() {
  Date a;
  initDate(&a);
  printDate(a);
  readDate(&a);
  printDate(a);
  return 0;
}