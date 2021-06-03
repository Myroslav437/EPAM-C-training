#pragma once
#include "../commonh.hpp"
#include <ostream>
#include <functional>

class TablePrinter {
public:
    typedef std::function<void(int, int, std::string)> Owner;

    static const Owner defaultOwner;

    static void print(const Table& t);
    static int getMaxCellWidth();
    static void setMaxCellWidth(int);
    static void setOwner(const Owner& );

protected:
    static std::vector<int> setXWidths(Table& t);
    static int setYWidths(const TableRow& t);
    static std::string formSolidLine(const std::vector<int>&);
    static void sendRow(TableRow&, std::vector<int>, int);
private:
    static int maxCellWidth;
    static Owner owner;
};