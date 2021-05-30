#include <iostream>
#include <future>
#include "Calculator/Calculator.hpp"

int main(int argc, char* argv[]) {
    Calculator calc;
    std::string expr;

    // concat all arguments:
    for(int i = 1; i < argc; ++i) {
        expr.append(argv[i]);
    }
    calc.setExpression(expr);

    // run calculator:
    auto fut = std::async(std::launch::async, &Calculator::calculate, &calc);
    std::cout << fut.get() << std::endl;

    return 0;
}