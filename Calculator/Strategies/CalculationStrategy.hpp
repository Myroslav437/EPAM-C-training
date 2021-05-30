#pragma once

#include <string>

class CalculationStrategy {
public:
    virtual double evaluate(const std::string&) = 0;
};