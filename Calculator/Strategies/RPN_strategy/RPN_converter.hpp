#pragma once

#include <string>
#include <map>

class RPN_converter {
public:
    std::string convert(const std::string&);
    
private:
    std::string toNormalView(const std::string&);
    static const std::map<char, int> op_priority;
};
