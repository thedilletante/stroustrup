#include <iostream>
#include <limits>

#define PRINT(A) std::cout<<#A" = "<<(A)<<"\n"
#define LIMIT(TYPE, LIM) std::numeric_limits<TYPE>::LIM()
#define MAX(TYPE) LIMIT(TYPE, max)
#define MIN(TYPE) LIMIT(TYPE, min)

int main()
{
  //PRINT(1 / 0);
  PRINT(1 / (double)0);
  PRINT(MAX(int) + MAX(int));
  PRINT((double)MAX(int) + MAX(int));
  PRINT((double)(MAX(int) + MAX(int)));
  PRINT(MIN(double));
  PRINT(MIN(double)/MAX(double));
  return 0;
}