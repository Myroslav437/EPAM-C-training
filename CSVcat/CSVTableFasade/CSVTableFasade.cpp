#include "CSVTableFasade.hpp"
#include "../CSVParser/CSVParser.hpp"
#include "../TablePrinter/TablePrinter.hpp"

using namespace std;

void CSVTableFasade::printTable(const Table& t) {
    TablePrinter pr;
    pr.setOwner([](int x, int y, string st){
        cout << st;
        cout.flush(); //DEBUG
    });

    pr.setMaxCellWidth(20);
    pr.print(t);
}

Table CSVTableFasade::readTable(std::istream& is) {
    CSVParser pr;
    Table res = pr.parse(is);
    return res;
}