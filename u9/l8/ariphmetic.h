#ifndef CALC_ARIPHMETIC
#define CALC_ARIPHMETIC

#include <limits>

namespace Ariphmetic {

  class overflow {};
  class loss_of_accuracy {};


  double plus(double a, double b);
  double minus(double a, double b);
  double multiply(double a, double b);
  double divide(double a, double b);
}


#endif // CALC_ARIPHMETIC