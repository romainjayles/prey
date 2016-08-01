//
// Created by jaylesr on 20/06/16.
//

#include <Prey.h>
#include <Orientation_manager.h>
#include <config.h>

#include <stdio.h>

Prey::Prey(Logger &logger): logger(logger), orientation_manager(logger){
    current_state = SLEEPING;
}

int Prey::init(){
    logger.log(LOG_INFO, "Launching orientation manager");
    orientation_manager.init(ORIENTATION_MANAGER_UPDATE_FREQUENCY_MS);
}

int Prey::teardown(){
    logger.log(LOG_INFO, "Terminate Prey");
    orientation_manager.teardown();
    logger.log(LOG_INFO, "Prey terminated\n");
}
