#ifndef __ENDLINE_AGENT__H
#define __ENDLINE_AGENT__H 

#include "enviro.h"

using namespace enviro;
// Endline controller class
class EndlineController : public Process, public AgentInterface {

    public:
    EndlineController() {};

    void init() {};
    void start() {};
    void update() {};
    void stop() {};

};
// Endline agent class
class Endline : public Agent {
    public:
    Endline(json spec, World& world) : Agent(spec, world) {
        add_process(bc);
    }
    private:
    EndlineController bc;

};

DECLARE_INTERFACE(Endline)

#endif