#include "RPN_converter.hpp"
#include <algorithm>
#include <stack>

const std::map<char, int> RPN_converter::op_priority {
    {'_', 3},
    {'*', 2}, {'/', 2},
    {'-', 1}, {'+', 1}
};

std::string RPN_converter::convert(const std::string &str) {
    std::string RPN;
    std::stack<char> stk;
    std::string norm = toNormalView(str);

    // convert exp to reverse Polish notation using shunting-yard algorithm:
    for (auto i = norm.begin(); i < norm.end();) {
        //token - number:
        if (isdigit(*i)) {
            while (i != norm.end() && (isdigit(*i) || *i == '.'))
                RPN.push_back(*(i++));
            RPN.push_back(' ');
        }

        // token - operator:
        if (i != norm.end() && (op_priority.find(*i) != op_priority.end())) {
            while (!stk.empty() && op_priority.find(stk.top()) != op_priority.end() &&
                   op_priority.at(stk.top()) >= op_priority.at(*i)) 
            {
                RPN.push_back(stk.top());
                stk.pop();
            }
            stk.push(*i);
        }

        // token - opening bracket:
        if (i != norm.end() && (*i == '(')) {
            stk.push(*i);
        }

        //token - closing bracket:
        if (i != norm.end() && (*i == ')')) {
            while (stk.top() != '(') {
                RPN.push_back(stk.top());
                stk.pop();
            }
            stk.pop();
        }

        if (i != norm.end()) {
            ++i;
        }
    }

    while (!stk.empty()) {
        RPN.push_back(stk.top());
        stk.pop();
    }

    return RPN;
}

std::string RPN_converter::toNormalView(const std::string& str) {
    std::string res(str);

    // remove separators:
    const std::string delim = " \t\n\r";  // small string
    for(const auto c : delim) {
        const auto it = std::remove(res.begin(), res.end(), c);
        res.erase(it, res.end());
    }
    
    // change unary minuses to '_': 
    char pr = 0;
    const std::string op("+-*/(");
    const auto tr_f = [&pr, &op](char c) -> char {
        if (c == '-' && op.find(pr) != std::string::npos) {
            c = '_';
        }
        pr = c;
        return pr;
    };
    std::transform(res.begin(), res.end(), res.begin(), tr_f);

    return res;
}