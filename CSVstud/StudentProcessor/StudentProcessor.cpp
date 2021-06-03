#include "StudentProcessor.hpp"
#include <stdexcept>

using namespace std;

const double StudentProcessor::defaultSucceedPoints = 5.0;
const int StudentProcessor::defaultSucceedAttendency = 5;

StudentProcessor::StudentProcessor() : 
    succeedPoints(defaultSucceedPoints),
    succeedAttendency(defaultSucceedAttendency)
{
}

double StudentProcessor::getSucceedPoints() {
    return succeedPoints;
}

void StudentProcessor::setSucceedPoints(double p) {
    succeedPoints = p;
}

int StudentProcessor::getSucceedAttendency() {
    return succeedAttendency;
}

void StudentProcessor::setSucceedPAttendency(int a) {
    succeedAttendency = a;
}

void StudentProcessor::process(Table& t) {
    const size_t avgMarkRow = 2;
    const size_t attendentRow = 3;

    double avgMark = 0;
    int attendancy = 0;
    for(int i = 0; i < t.size(); ++i) {
        try { 
            auto& frow = t.at(i);
            if(i == 0) {
                frow.insert(frow.begin(), 1, "Succeeded");
                continue;
            }
            avgMark = std::stod(frow.at(avgMarkRow));
            attendancy = std::stoi(frow.at(attendentRow));

            string res = "";
            if(avgMark >= succeedPoints && attendancy >= succeedAttendency) {
                res = "+";
            }
            
            frow.insert(frow.begin(), 1, res);
        }
        catch(const std::out_of_range& e) {
            string exm = "Error occured: table is ill - formed\n";
            exm +=  "\t" + string(e.what());
            throw std::logic_error(exm);
        }
        catch(const std::invalid_argument& e) {
            string exm = "Error occured: average mark should be a real number and attendancy should be an integer\n";
            exm +=  "\t" + string(e.what());
            throw std::logic_error(exm);
        }
    }
}