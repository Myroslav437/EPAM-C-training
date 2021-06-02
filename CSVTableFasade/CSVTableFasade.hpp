#pragma once
#include <iostream>
#include "../commonh.hpp"

class CSVTableFasade {
public:
    void printTable(const Table&);
    Table readTable(std::istream&);
};
