#ifndef __Robot_AGENT__H
#define __Robot_AGENT__H

#include <string>
#include <math.h>
#include "enviro.h"

namespace
{

    using namespace enviro;

    class RobotController : public Process, public AgentInterface {
        public:
        RobotController() {};
        void init();
        void start() {};
        void update() {};
        void stop() {}

    };

    class Robot : public Agent
    {

    public:
        Robot(json spec, World &world) : Agent(spec, world)
        {
            add_process(rc);
        }

        RobotController rc;
    };

    DECLARE_INTERFACE(Robot);

}

#endif