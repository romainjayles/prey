//
// Created by jaylesr on 20/06/16.
//

#ifndef _PREY_H_
#define _PREY_H_

#include <Orientation_manager.h>
#include <Flight_controller.h>
#include <GPS.h>
#include <GPS_mock.h>
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

    Flight_controller flight_controller;
    GPS_mock gps;

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

#endif //_PREY_H_
