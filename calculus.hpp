#ifndef CALCULUS_HPP
#define CALCULUS_HPP

#include <functional>

double integrate (double a, double b, unsigned int n, std::function<double (double)> f);

#endif
