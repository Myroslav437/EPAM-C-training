#include <iostream>
#include <fstream>
#include "CSVTableFasade/CSVTableFasade.hpp"

int main(int argc, char *argv[]) {
    std::ifstream ifs;
    std::string path;

    if(argc < 2) {
        std::cout << "No path specified" << std::endl;
    }

    // concat path
    for(int i = 1; i < argc; ++i) {
        path.append(argv[i]);
    }

    ifs.open(path);
    if(!ifs.is_open()) {
        std::cout << "Can't find file specified" << std::endl;
        return 1;
    }

    CSVTableFasade fs;
    Table T;
    try {
        T = fs.readTable(ifs);
    }
    catch(...) {
        std::cout << "Error while reading CSV file" << std::endl;
    }
    try {
        fs.printTable(T);
    }
    catch(...) {
        std::cout << "Error while printing CSV file" << std::endl;
    }

    std::cout << std::endl;
    return 0;
}

