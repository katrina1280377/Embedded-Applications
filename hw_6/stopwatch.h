#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <chrono>
#include <thread>

using namespace std::chrono;

class Stopwatch {
private:
    high_resolution_clock::time_point start_time;
    high_resolution_clock::time_point end_time;
    bool running = false;
    long long elapsed = 0;

public:
    void start();
    void stop();
    void reset();
    double get_minutes();
    double get_seconds();
    double get_milliseconds();
    double get_nanoseconds();
};

#endif // STOPWATCH_H