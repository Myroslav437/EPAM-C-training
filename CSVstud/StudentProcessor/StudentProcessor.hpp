#pragma once
#include "../../CSVcat/commonh.hpp"

class StudentProcessor {
public:
    StudentProcessor();
    void process(Table&);
    double getSucceedPoints();
    void setSucceedPoints(double);
    int getSucceedAttendency();
    void setSucceedPAttendency(int);

protected:
    double succeedPoints;
    int succeedAttendency;
    static const double defaultSucceedPoints;
    static const int defaultSucceedAttendency;
};
