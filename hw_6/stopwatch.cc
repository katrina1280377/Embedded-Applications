#include "stopwatch.h"

void Stopwatch::start() {
    start_time = high_resolution_clock::now();
    running = true;
}

void Stopwatch::stop() {
    if (running) {
        end_time = high_resolution_clock::now();
        elapsed += duration_cast<nanoseconds>(end_time - start_time).count();
        running = false;
    }
}

void Stopwatch::reset() {
    high_resolution_clock::time_point zero;
    start_time = zero;
    end_time = zero;
    elapsed = 0;
    running = false;
}


double Stopwatch::get_minutes() {
    return get_seconds() / 60.0;
}

double Stopwatch::get_seconds() {
    return get_milliseconds() / 1000.0;
}

double Stopwatch::get_milliseconds() {
    return get_nanoseconds() / 1e6;
}

double Stopwatch::get_nanoseconds() {
    if (running) {
        stop();
        start();
    }
    return elapsed;
}