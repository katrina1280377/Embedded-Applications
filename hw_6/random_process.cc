#include "random_process.h"
#include <cstdlib>
#include <ctime>

RandomProcess::RandomProcess(string name) : Process(name) {}

void RandomProcess::init() {}

void RandomProcess::start() {}

void RandomProcess::update() {
    double random_value = ((double) rand() / RAND_MAX);
    channel("link").send(random_value);
}
void RandomProcess::stop() {}
