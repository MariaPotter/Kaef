#ifndef CALCULUS_HPP
#define CALCULUS_HPP

#include <functional>

double integrate(double a, double b, int n, std::function<double(double)> f);

#endif