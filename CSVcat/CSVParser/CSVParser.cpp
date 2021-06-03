#include "CSVParser.hpp"

using namespace std;

Table CSVParser::parse(std::istream& is) {
    Table res;
    string buf;

    while(is.good()) {
        getline(is, buf);

        if(buf.empty()) {
            continue;
        }
        while(buf.back() == '\n' || buf.back() == '\t' || buf.back() == ' ' || buf.back() == '\r') {
            buf.pop_back();
        }

        const TableRow rw = parseRowString(buf);
        res.emplace_back(rw);
    }

    return res;
}

TableRow CSVParser::parseRowString(const std::string& s) {
    TableRow res;
    string buf = "";
    int qMarkAmount = 0;

    const auto reset = [&] {
        buf.clear();
        qMarkAmount = 0;
    };

    for(const auto c : s) {
        if(c != ',' && c != '"') {
            buf.push_back(c);
        }
        else if(qMarkAmount == 0 && c == ',') {
            res.push_back(buf);
            reset();
        }
        else if(qMarkAmount == 0 && c == '"') {
            ++qMarkAmount;
        }
        else if(qMarkAmount != 0 && c == '"') {
            buf.push_back(c);
            ++qMarkAmount;
        }
        else if(qMarkAmount != 0 && qMarkAmount % 2 != 0 && c == ',') {
            buf.push_back(c);
        }
        else if(qMarkAmount != 0 && qMarkAmount % 2 == 0 && c == ',') {
            buf.pop_back();
            remove_2adjacent(buf, '"');
            res.push_back(buf);
            reset();
        }
    }

    if(!buf.empty()) {
        res.push_back(buf);
    }

    return res;
}

int CSVParser::remove_2adjacent(std::string& s, char ch) {
    char prev = '\0';
    int count = 0;

    for(int i = 0; i < s.size(); ++i) {
        const char v = s[i];
        if(v == ch && prev == ch) {
            s.erase(s.begin() + i);
            prev = '\0';
            ++count;
            i--;
        }
        else {
            prev = v;
        }
    }
    
    return count;
}