#ifndef FILTER_H
#define FILTER_H

#include <random>
#include <deque>
#include "elma/elma.h"

using namespace std;
using namespace elma;

class Filter : public Process {
public:
    Filter(string name);
    void init();
    void start();
    void update();
    void stop();
    double value();

private:
    deque<double> values;
    double sum;
    int count;
};


#endif // FILTER_H