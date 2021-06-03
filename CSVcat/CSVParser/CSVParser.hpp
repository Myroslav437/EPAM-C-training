#pragma once
#include "../commonh.hpp"
#include <istream>

class CSVParser {
public:
    static Table parse(std::istream&);
    
private:
    static TableRow parseRowString(const std::string&);
    static int remove_2adjacent(std::string&, char);
};