#include "filter.h"

Filter::Filter(string name) : Process(name), sum(0), count(0) {}

void Filter::init() {}

void Filter::start() {}

void Filter::update() {
    double value = channel("link").latest();
    sum += value;
    values.push_back(value);
    if (values.size() > 10) {
        sum -= values.front();
        values.pop_front();
    }

    count = values.size();
}

void Filter::stop() {}

double Filter::value() {
    if (count == 0) {
        return 0;
    } else {
        return sum / count;
    }
}