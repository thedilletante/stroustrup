#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>


template<class T1, class T2>
class TPair : public std::pair<T1, T2> {
public:

  friend std::ostream & operator<<(std::ostream & os, const TPair & p) {
    return os<<p.first<<"\t"<<p.second;
  }

  friend std::istream & operator>>(std::istream & is, TPair & p) {
    return is>>p.first>>p.second;
  }

};

typedef TPair<std::string, double> kv;
typedef std::istream_iterator<kv> in_kv;

bool TPairSort(const kv & a1, const kv & a2) {
  return a1.second < a2.second;
}

int main() {
  in_kv ii(std::cin);
  in_kv eos;

  std::vector<kv> in(ii, eos);

  double summ = 0;
  unsigned count = 0;

  std::map<std::string, double> avg;
  std::map<std::string, unsigned> counter;

  for (std::vector<kv>::const_iterator i = in.begin(), end = in.end() ; i != end; ++i) {
    summ += avg[i->first] += i->second;
    ++count;
    ++counter[i->first];
  }

  if (count > 0) {
    for (std::map<std::string, unsigned>::const_iterator i = counter.begin(), end = counter.end(); i != end; ++i) {
      std::cout<<i->first<<"\t"<<i->second<<"\t"<<avg[i->first]<<"\t"<<(avg[i->first] / i->second)<<"\n";
    }

    std::sort(in.begin(), in.end(), TPairSort);

    double mediana = 0;

    if (count % 2 == 0) {
      mediana = (in.at(count / 2 - 1).second + in.at(count / 2).second) / 2.0;
    }
    else {
      mediana = in.at(count / 2).second;
    }

    std::cout<<"__________________\n";
    std::cout<<"Amount:___________\n";
    std::cout<<summ<<"\t"<<(summ / count)<<"\n";
    std::cout<<"Mediana = "<<mediana<<"\n";
    std::cout<<"__________________\n";

    std::ostream_iterator<kv> oo(std::cout, "\n");

    std::copy(in.begin(), in.end(), oo);
  }

  return 0;
}