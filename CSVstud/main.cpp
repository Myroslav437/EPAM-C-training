#include <iostream>
#include <fstream>
#include "../CSVcat/CSVTableFasade/CSVTableFasade.hpp"
#include "StudentProcessor/StudentProcessor.hpp"

int main(int argc, char *argv[]) {
    std::ifstream ifs;
    std::string path;

    /*
    if(argc < 2) {
        std::cout << "No path specified" << std::endl;
    }

    // concat path
    for(int i = 1; i < argc; ++i) {
        path.append(argv[i]);
    }
    */
    path = "samples/StudentSample1.csv";
   //

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
    catch(const std::exception& e) {
        std::cout << "Error while reading CSV file: " << std::endl;
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch(...) {
        std::cout << "Unknown error occured while reading CSV file" << std::endl;
        return 1;
    }

    StudentProcessor pr;
    pr.setSucceedPoints(4);
    pr.setSucceedPAttendency(5);
    try {
        pr.process(T);
    }
    catch(const std::exception& e) {
        std::cout << "Error while processing the table: " << std::endl;
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch(...) {
        std::cout << "Unknown error occured while processing the table" << std::endl;
        return 1;
    }

    try {
        fs.printTable(T);
    }
    catch(const std::exception& e) {
        std::cout << "Error while printing the table: " << std::endl;
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch(...) {
        std::cout << "Unknown error while printing the table" << std::endl;
        return 1;
    }

    std::cout << std::endl;
    return 0;
}

