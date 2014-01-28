#include <iostream>
#include <iomanip>

void print(int * array, size_t dim);
void transponize(int * array, size_t dim);

int main() {
  int ar[] = {1,2,3,4,5,6,7,8,9};
  print(ar, 3);
  transponize(ar, 3);
  std::cout<<"_________________"<<std::endl;
  print(ar, 3); 
  return 0;
}

void print(int * array, size_t dim) {
  for ( size_t i = 0; i < dim; ++i ) {
    for ( size_t j = 0; j < dim; ++j ) {
      std::cout.width( 5 );
      std::cout<<array[ i*dim + j ];
    }
    std::cout<<std::endl;
  }
}

void transponize(int * array, size_t dim) {
  int tmp = 0;
  for ( size_t i = 0; i < dim; ++i ) {
    for ( size_t j = 0; j < i; ++j ) {
      tmp = array[ i*dim + j ];
      array[ i*dim + j ] = array[ j*dim + i ];
      array[ j*dim + i ] = tmp;
    }
  }
}