#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>
#include <string>

template<class T>
void error(T code, std::string msg) {
    std::cerr << "Error: " << msg << std::endl;
    throw code;
}

#endif