#include "ariphmetic.h"


double Ariphmetic::plus(double a, double b) {
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

double Ariphmetic::minus(double a, double b) {
  return plus(a, -b);
}

double Ariphmetic::multiply(double a, double b) {
  double result = a * b;
  if (result / a != b) throw loss_of_accuracy();
  return result;
}

double Ariphmetic::divide(double a, double b) {
  double result = a / b;
  if (result * b != a) throw loss_of_accuracy();
  return a / b;
}