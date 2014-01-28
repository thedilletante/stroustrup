#include <iostream>

struct Date {
  unsigned y, m, d;
};

bool leap(int year) {
	return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
}

int getMaxDay(int month, int year) {
  switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
      return 31;
    case 2:
      return 28 + leap(year);
    default:
      return 30;
  }
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
  		int max = getMaxDay(m, y);
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

void addYear(Date * date) {
  if (leap(date->y) && date->m == 2 && date->d == 29) {
    --date->d;
  }
  ++date->y;
}

void addMonth(Date * date) {
  if (date->m == 12) {
    addYear(date);
    date->m = 1;
  }
  else {
    ++date->m;
    int max = getMaxDay(date->m, date->y);
    if (date->d > max) {
      date->d = max;
    }
  }
}

void addDay(Date * date) {
  if (date->d == getMaxDay(date->m, date->y)) {
    date->d = 1;
    addMonth(date);
  }
  else {
    ++date->d;
  }
}

enum WEEKDAY {
  SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

WEEKDAY getWeekDay(const Date & date) {
  int a = (14 - date.m) / 12;
  int y = date.y - a;
  int m = date.m + 12 * a - 2;
  int result = (7000 + (date.d + y + y/4 -y/100 + y/400 + (31*m)/12)) % 7;
  return WEEKDAY(result);
}

Date firstMonday(const Date& date) {
  Date a;
  a.y = date.y;
  a.m = date.m;
  a.d = date.d;
  while(getWeekDay(a) != MONDAY) {
    addDay(&a);
  }
  return a;
}

std::ostream & operator<<( std::ostream& os, const WEEKDAY& weekday) {
#define SELDON(name) case name: os << #name; break
  switch(weekday) {
    SELDON(SUNDAY); SELDON(MONDAY); SELDON(TUESDAY);
    SELDON(WEDNESDAY); SELDON(THURSDAY); SELDON(FRIDAY);
    SELDON(SATURDAY);
  }
#undef SELDON
  return os;
}

int main() {
  Date a;
  initDate(&a);
  printDate(a);
  readDate(&a);
  printDate(a);
  std::cout << getWeekDay( a ) << std::endl;
  std::cout << "addDay" << std::endl;
  addDay(&a);
  printDate(a);
  std::cout << getWeekDay( a ) << std::endl;
  std::cout << "addMonth" << std::endl;
  addMonth(&a);
  printDate(a);
  std::cout << getWeekDay( a ) << std::endl;
  std::cout << "addYear" << std::endl;
  addYear(&a);
  printDate(a);
  std::cout << getWeekDay( a ) << std::endl;
  std::cout << "nextMonday" << std::endl;
  printDate(firstMonday(a));
  return 0;
}