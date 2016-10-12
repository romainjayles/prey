/**
 * Allow to draw some curves on the PID from the flight controller, and help debugging PID working
 */

//
// Created by jaylesr on 11/08/16.
//

/*
 * Used to output the orientation, for debug use
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include <Flight_controller.h>
#include <Logger.h>

static bool run;
void handler(int v) {
    run = false;
}


int main(int argv, char **argc){

    Logger logger(LOG_ERROR);
    signal(SIGINT, handler);

    Flight_controller flight_controller(logger);
    if(flight_controller.init(ORIENTATION_MANAGER_UPDATE_FREQUENCY_MS) == -1){
        logger.log(LOG_ERROR, "Error with the init of orientation_manager");
        return -1;
    }

    run = true;
    while(run){
        usleep(ORIENTATION_MANAGER_UPDATE_FREQUENCY_MS*1000);
    }
    flight_controller.teardown();

    return 0;
}

