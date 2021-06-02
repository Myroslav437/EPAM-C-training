#include "TablePrinter.hpp"
#include <mutex>
#include <algorithm>

int TablePrinter::maxCellWidth = 10;
const TablePrinter::Owner TablePrinter::defaultOwner = [](int, int, std::string ){};
TablePrinter::Owner TablePrinter::owner = defaultOwner;

using namespace std;

 int TablePrinter::getMaxCellWidth() {
     return maxCellWidth;
 }

void TablePrinter::setMaxCellWidth(int v) {
    maxCellWidth = v;
}

void TablePrinter::setOwner(const Owner& o) {
    owner = o;
}

void TablePrinter::print(const Table& t) {
    Table tCopy = t; 
    vector<int> xWidth = setXWidths(tCopy);

    const string line = formSolidLine(xWidth);
    for(int i = 0; i < t.size(); ++i) {
        owner(-1, -1, line);
        sendRow(tCopy[i], xWidth, i);
        owner(-1, -1, "\n");
    }
    owner(-1, -1, line);
}

void TablePrinter::sendRow(TableRow& t, std::vector<int> x, int y_pos) {
    int y_w = setYWidths(t);
    vector<string::iterator> itv;
    for(int i = 0; i < t.size(); ++i) {
        itv.push_back(t[i].begin());
    }

    for(int y = 0; y < y_w; ++y) {
        owner(-1, -1, "\n|");
        int i;
        for(i = 0; i < t.size(); ++i) {
            auto tmp = std::find(itv[i], t[i].end(), '\n');
            string subst = string(itv[i], tmp);
            subst += string(x[i] - subst.length(), ' ');

            if(tmp == t[i].end()) {
                itv[i] = t[i].end();
            }
            else {
                itv[i] = tmp + 1;
            }
            owner(-1, -1, " ");
            owner(i, y_pos, subst);
            owner(-1, -1, " |");
        }
        while(i < x.size()) {
            owner(-1, -1, " ");
            owner(i, y_pos, string(x[i], ' '));
            owner(-1, -1, " |");
            ++i;
        }
    }
}

vector<int> TablePrinter::setXWidths(Table& t) {
    vector<int> res;
    int maxX = 0;

    for(int i = 0; i < t.size(); ++i) {
        if(maxX < t[i].size()) {
            maxX = t[i].size();
        }
    }

    for(int x = 0; x < maxX; ++x) {
        int w = 0;
        for(int y = 0; y < t.size(); ++y) {
            if(t[y].size() <= x) {
                continue;
            }
            if(t[y][x].length() > maxCellWidth) {
                w = maxCellWidth;
                for(int i = 1; t[y][x].length() > maxCellWidth * i + i - 1; ++i) {
                    t[y][x].insert(maxCellWidth * i + i - 1, "\n");
                }
            }
            else if(w < t[y][x].length()) {
                w = t[y][x].length();
            }
        }
        res.push_back(w);
    }

    return res;
}

int TablePrinter::setYWidths(const TableRow& t) {
    int w = 0;
    for(int x = 0; x < t.size(); ++x) {
        const int tmp = std::count(t[x].begin(), t[x].end(), '\n') + 1;
        if(w < tmp) {
            w = tmp;
        }
    }

    return w;
}

string TablePrinter::formSolidLine(const std::vector<int>& v) {
    string res;
    for(int i = 0; i < v.size(); ++i) {
        res += "+" + string(v[i] + 2, '-');
    } 
    res += "+";

    return res;
}