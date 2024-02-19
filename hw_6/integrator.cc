#include "integrator.h"
#include <iostream>

Integrator::Integrator(string name) : Process(name), integral(0.0) {}

void Integrator::init() {}
void Integrator::start() {}
void Integrator::stop() {}

void Integrator::update() {
    double value = channel("link").latest();
    integral += delta() * value;
}
double Integrator::value() const {
    return integral;
}
