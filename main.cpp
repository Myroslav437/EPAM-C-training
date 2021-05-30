#include <iostream>
#include <future>
#include "Calculator/Calculator.hpp"

int main(int argc, char* argv[]) {
    Calculator calc;
    std::string expr;

    // concat all arguments:
    if(argc < 2) {
        std::cout << "No expression passed" << std::endl;
        return 1;
    }
    for(int i = 1; i < argc; ++i) {
        expr.append(argv[i]);
    }
    calc.setExpression(expr);

    // run calculator:
    try {
        auto fut = std::async(std::launch::async, &Calculator::calculate, &calc);
        std::cout << fut.get() << std::endl;
    }
    catch(...) {
        std::cout << "Error occured" << std::endl;
    }
    return 0;
}