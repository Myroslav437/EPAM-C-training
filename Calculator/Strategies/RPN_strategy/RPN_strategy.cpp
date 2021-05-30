#include "RPN_strategy.hpp"


double RPN_strategy::evaluate(const std::string& str) {
    std::string converted = conv.convert(str);
    double res = eval.evaluate(converted);
    return res;
}