#ifndef TOOL_HPP
#define TOOL_HPP

#include <vector>
#include <algorithm>
#include <iostream>

#include <cstdlib>

#include "error.hpp"

extern const double k1;
extern const double k2;

template <class T>  T abs(T x){return (x>0)?x:-x;}

class Tool {
    std::vector<double> coeff_;
    bool is_zero_;
    double eps_;
public:
    Tool(std::vector<double> coeff, double eps=1e-14) {
        while(true) {
            if(coeff.size() == 0) {
                break;
            }

            if(abs(coeff.back()) < eps) {
                coeff.pop_back();
            } else {
                break;
            }
        } 

        coeff_ = coeff;
        is_zero_ = coeff.size() == 0;
        eps_ = eps;
    }

    int deg() const {
        return static_cast<int>(coeff_.size()) - 1;
    }

    double operator()(double x) const {
        int d = deg(); 
        
        if(d == -1) return 0;
        else {
            double ret = 0;

            for(int i = d; i >= 0; --i) {
                ret *= x;
                ret += coeff_[i];
            }

            return ret;
        }
    }

    Tool derivative() const {
        int d = deg();

        if (d == -1 || d == 0) {
            return Tool({0});
        } else {
            std::vector<double> result(d);

            for (int i = 0; i < d; ++i) {
                result[i] = (i + 1) * coeff_[i + 1];
            }

            return Tool(result);
        }
    }

    double integrate(double a, double b) const {
        int d = deg();

        std::vector<double> result(d + 2);

        result[0] = 0;
        for(int i = 1; i < d + 2; ++i) {
            result[i] = coeff_[i - 1] / i;
        }

        Tool ad(result);

        return ad(b) - ad(a);
    }

    void print() const {
        int d = deg();

        if(d == -1) std::cout << 0;
        else {
            for(int i = 0; i < d + 1; ++i) {
                if(i == 0) std::cout << coeff_[0];
                else if(i == 1) {
                    if(abs(coeff_[i]) < eps_) {
                        continue;
                    }
                    else if(coeff_[i] > 0) {
                        std::cout << "+" << coeff_[i] << "x";
                    }
                    else {
                        std::cout << coeff_[i] << "x";
                    } 
                }
                else {
                    if(abs(coeff_[i]) < eps_) {
                        continue;
                    }
                    else if(coeff_[i] > 0) {
                        std::cout << "+" << coeff_[i] << "x^" << i;
                    }
                    else {
                        std::cout << coeff_[i] << "x^" << i;
                    }
                }    
            }

            std::cout << std::endl;
        }
    }

    friend Tool operator+(const Tool&, const Tool&);
    friend Tool operator-(const Tool&);
    friend Tool operator-(const Tool&, const Tool&);
    friend Tool operator*(const Tool&, const Tool&);
};

class ToolWithSupp {
    Tool tool_;
    int start_;
    int end_;
    int N_;
public:
    ToolWithSupp(Tool tool, int start, int end, int N) : tool_(tool), start_(start), end_(end), N_(N) {
        // if (N % 2 == 1) error(-1, "N is odd");

        start_ = std::max(start_, 0);
        end_ = std::min(end_, N_);
    };

    ToolWithSupp derivative() const {
        return ToolWithSupp(tool_.derivative(), start_, end_, N_);
    }

    double integrate(bool enable_k) {
        if (end_ - start_ == 0) {
            return 0;
        }
        else if (end_ - start_ == 1) {
            double a = static_cast<double>(start_) / N_;
            double c = static_cast<double>(end_) / N_;
            double b = (a + c) / 2;

            if (N_ % 2 == 0) { // N_ is even
                double k = 1;
                if (enable_k) {
                    k = end_ <= N_ / 2 ? k1 : k2;
                }

                return k * tool_.integrate(a, c);
            } else { // N_ is odd
                if (enable_k) {
                    if (end_ + start_ == N_ && enable_k) return k1 * tool_.integrate(a, b) + k2 * tool_.integrate(b, c);
                    else if (end_ <= N_ / 2) return k1 * tool_.integrate(a, c);
                    else return k2 * tool_.integrate(a, c);
                }
                else {
                    return tool_.integrate(a, c);
                }
            }
            
        }
        else if (end_ - start_ == 2) {
            auto p1 = ToolWithSupp(tool_, start_, end_ - 1, N_);
            auto p2 = ToolWithSupp(tool_, start_ + 1, end_, N_);

            return p1.integrate(enable_k) + p2.integrate(enable_k);
        }
        else {
            printf("start_: %d, end_: %d\n", start_, end_);
            error(-1, "supp is too big or bad");
            return 0;
        }
    }

    friend ToolWithSupp operator+(const ToolWithSupp&, const ToolWithSupp&);
    friend ToolWithSupp operator-(const ToolWithSupp&);
    friend ToolWithSupp operator-(const ToolWithSupp&, const ToolWithSupp&);
    friend ToolWithSupp operator*(const ToolWithSupp&, const ToolWithSupp&);
};

#endif