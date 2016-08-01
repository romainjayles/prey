//
// Created by jaylesr on 20/06/16.
//

#ifndef PREY_PREY_H
#define PREY_PREY_H

#include <Orientation_manager.h>
#include <Logger.h>

/**
 * The different states of the uav
 */
enum State{
    SLEEPING,
    ERROR,
    STATIONARY,
    MOVING
};

/**
 * This is the main class of the project, the one the user will refer to interact with the UAV.
 */
class Prey
{
private:
    //The actual state of the uav
    State current_state;

    Orientation_manager orientation_manager;

    Logger &logger;


public:
    Prey(Logger &logger);

    int init();

    int teardown();

    State get_state();

    int go_to_point(double latitude, double longitude, int altitude);

    int land(double latitude, double longitude);

    int land();
};

#endif //PREY_PREY_H
