#include <functional>

#include "error.hpp"

using namespace std;

double integrate(double a, double b, int n, function<double(double)> f) {
    if (n < 2) error(-1, "n < 2 in integrate");

    double h = (b - a) / (n - 1);

    double result = 0;
    for(int i = 0; i < (n - 1); ++i) {
        double x = a + h * (static_cast<double>(i) + 0.5);

        double val = f(x);
        result += val * h;
    }

    return result;
}