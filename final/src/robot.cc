#include <iostream>
#include <math.h>
#include "robot.h"

using namespace enviro;

void RobotController::init() {
    if (sensor_value(0) > 40) // if the robot is near the wall
    {
        track_velocity(0, 0); // stop moving
    } else {
	    watch("keydown", [&](Event &e) {
	        auto key = e.value()["key"].get<std::string>();
	        if (key == "w") {
	            track_velocity(10, 0); // move forward
	        } else if (key == "s") {
	            track_velocity(-10, 0); // move backward
	        } else if (key == "a") {
	            track_velocity(0, -5); // rotate left
	        } else if (key == "d") {
	            track_velocity(0, 5); // rotate right
	        }
	    });

	    watch("keyup", [&](Event &e) {
	        track_velocity(0, 0); // stop moving
	    });
	}

}
