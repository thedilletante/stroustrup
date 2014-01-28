#include <iostream>

struct Month {
  const char * name;
  int days;
};

int main() {
  const char * monthes[] = {  "January", "February", "March", 
                        "April", "May", "June", 
                        "July","August", "September", 
                        "October", "November", "December" };

  int days [] =      { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  std::cout<<"Print from arrays __________\n";
  for (unsigned cur = 0, end = sizeof(monthes)/sizeof(*monthes) - 1; cur < end; ++cur) {
    std::cout<<monthes[cur]<<" - "<<days[cur]<<" days\n";
  }

  Month s_monthes[] = {  { "January", 31 }, { "February", 28 }, { "March", 31 }, 
                        { "April", 30 }, { "May", 31 }, { "June", 30 }, 
                        { "July", 31 },{ "August", 31 }, { "September", 30 }, 
                        { "October", 31 }, { "November", 30 }, { "December", 31 } };

  std::cout<<"Print from struct __________\n";

  for (unsigned cur = 0, end = sizeof(s_monthes)/sizeof(*s_monthes) - 1; cur < end; ++cur) {
    std::cout<<s_monthes[cur].name<<" - "<<s_monthes[cur].days<<" days\n";
  }

  return 0;
}