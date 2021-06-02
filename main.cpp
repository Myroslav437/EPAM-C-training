#include <iostream>
#include "CSVTableFasade/CSVTableFasade.hpp"
#include <fstream>

int main() {
    std::ifstream ifs;
    ifs.open("samples/OutputOverloadSample2.csv");
    if(!ifs.is_open()) {
        std::cout << "Can't find file specified" << std::endl;
        return 1;
    }

    CSVTableFasade fs;
    auto T = fs.readTable(ifs);
    fs.printTable(T);
    std::cout << std::endl;
}

