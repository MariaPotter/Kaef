#ifndef BASIC_F_HPP
#define BASIC_F_HPP

#include <functional>
#include <vector>

std::vector<std::vector<double>> gen_diag (int N);
std::vector<double> gen_f (int N, std::function<double (double)> f);
std::vector<std::vector<double>>
    matr_initial (std::vector<std::vector<double>> diag, std::vector<double> f);

#endif