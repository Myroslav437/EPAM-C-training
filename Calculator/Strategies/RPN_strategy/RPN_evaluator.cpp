#include "RPN_evaluator.hpp"
#include <stack>
#include <cstdlib>

double RPN_evaluator::evaluate(const std::string& rpn) {
    std::stack<double> res_stack;
    for (auto i = rpn.begin(); i < rpn.end();) {
        if (isdigit(*i)) {
            const char* it = &(*i);
            char *len;
            double num = strtod(it, &len);
            res_stack.push(num);
            i += (len - it); //
        }
        else if (*i == '_') {
            res_stack.top() = -res_stack.top();
        }
        else {
            double r2 = res_stack.top();
            res_stack.pop();
            switch (*i) {
            case '+':
                res_stack.top() += r2;
                break;
            case '-':
                res_stack.top() -= r2;
                break;
            case '*':
                res_stack.top() *= r2;
                break;
            case '/':
                res_stack.top() /= r2;
                break;
            }
        }

        if (i < rpn.end()) {
            ++i;
        }
    }
    return res_stack.top();
}