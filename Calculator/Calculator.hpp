#pragma once

#include <string>
#include <memory>

// Strategies:
#include "Strategies/CalculationStrategy.hpp"
#include "Strategies/RPN_strategy/RPN_strategy.hpp"

class Calculator {
    typedef double ResultType;
    typedef std::string ExpressionType;
    typedef RPN_strategy DefaultStrategy;

public:
    Calculator();
    Calculator(const std::string&);
    Calculator(Calculator&&) noexcept;
    Calculator(const Calculator&) = delete;

    Calculator& operator=(Calculator&&);
    Calculator& operator=(const Calculator&) = delete;

    ResultType calculate();
    void setExpression(const ExpressionType&);
    void setStragegy(CalculationStrategy&);

    ~Calculator();

private:
    std::shared_ptr<CalculationStrategy> strategy;
    ExpressionType expression;
};