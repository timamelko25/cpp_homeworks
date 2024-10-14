#pragma once
#include <string>
#include "loader.h"

class Calculator {
private:
    Loader& loader;

    double parse_expression(const std::string& expression, size_t& pos);
    double parse_term(const std::string& expression, size_t& pos);
    double parse_brackets(const std::string& expression, size_t& pos);
    void skip_spaces(const std::string& expression, size_t& pos);

    double call(const std::string& func_name, double arg);
    double call(const std::string& func_name, double arg1, double arg2);

public:
    Calculator(Loader& loader);

    ~Calculator();

    double method(const std::string& expression);
};
