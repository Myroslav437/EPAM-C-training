#pragma once

#include "../CalculationStrategy.hpp"
#include "RPN_converter.hpp"
#include "RPN_evaluator.hpp"

class RPN_strategy : CalculationStrategy {
public:
    double evaluate(const std::string&) override;
    
private:
    RPN_converter conv;
    RPN_evaluator eval;
};