#include "elma/elma.h"

using namespace elma;
using namespace std;

class Integrator : public Process {
public:
    Integrator(string name);
    void init() override;
    void start() override;
    void stop() override;
    void update() override;
    double value() const;

private:
    double integral;
};


class ConstantProcess : public Process {
public:
    ConstantProcess(string name, double constantValue) : Process(name), _value(constantValue) {}
    void init() {};
    void start() {};
    void stop() {};
    void update() {
        channel("link").send(_value);
    };
    double value() {
        return _value;
    };

private:
    double _value;
};