#include "Calculator.hpp"

Calculator::Calculator(const std::string& str) : 
    expression(str),
    strategy((CalculationStrategy*)(new DefaultStrategy())) {
}

Calculator::Calculator() : Calculator("") {
}

Calculator::Calculator(Calculator&& o) noexcept :
    strategy(std::move(o.strategy)),
    expression(std::move(o.expression)) {
}

Calculator& Calculator::operator=(Calculator&& o) {
    strategy = std::move(o.strategy);
    expression = std::move(o.expression);
    return *this;
}

Calculator::ResultType Calculator::calculate() {
    return strategy.get()->evaluate(expression);
}

void Calculator::setExpression(const ExpressionType& exp) {
    this->expression = exp;
}

void Calculator::setStragegy(CalculationStrategy& str) {
    std::shared_ptr<CalculationStrategy> newstrategy(&str);
    strategy.swap(newstrategy);
}

 Calculator::~Calculator() {
 }