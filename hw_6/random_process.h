#ifndef RANDOM_PROCESS_H
#define RANDOM_PROCESS_H

#include <elma/elma.h>

using namespace elma;
using namespace std;

class RandomProcess : public Process {
public:
    RandomProcess(string name);
    void init();
    void start();
    void update();
    void stop();
};

#endif