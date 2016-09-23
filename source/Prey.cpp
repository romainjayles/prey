//
// Created by jaylesr on 20/06/16.
//

#include <Prey.h>
#include <GPS.h>
#include <GPS_mock.h>
#include <Flight_controller.h>
#include <config.h>

#include <stdio.h>

Prey::Prey(Logger &logger): logger(logger), flight_controller(logger), gps(logger){
    current_state = SLEEPING;
}

int Prey::init(){
    logger.log(LOG_INFO, "Launching Flight Controller");
    flight_controller.init(FLIGHT_CONTROLLER_UPDATE_FREQUENCY_MS);
    logger.log(LOG_INFO, "Launching GPS");
    gps.init(GPS_UPDATE_FREQUENCY_MS);
}

int Prey::teardown(){
    logger.log(LOG_INFO, "Terminate Prey");
    flight_controller.teardown();
    gps.teardown();
    logger.log(LOG_INFO, "Prey terminated\n");
}
