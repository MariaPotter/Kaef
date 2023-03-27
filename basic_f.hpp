#ifndef BASIC_F_HPP
#define BASIC_F_HPP

#include <functional>
#include <vector>

std::vector<std::vector<double>> gen_diag (unsigned int N);
std::vector<double> gen_f (unsigned int N, std::function<double (double)> f);
std::vector<std::vector<double>>
    matr_initial (std::vector<std::vector<double>> diag, std::vector<double> f);

#endif
