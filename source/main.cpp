/**
 * This is the main entry point of the application
 */


#include <stdio.h>
#include <stdlib.h>

#include <Prey.h>
#include <Logger.h>

/**
 * This is the main entry point of the program,
 * It will take care of interfacing the user's will with the uav actions
 */
int main(int argv, char **argc){
    Logger logger(LOG_NONE);
    //Creation of the main interface class
    Prey prey(logger);
    //Initialization of the uav
    prey.init();
    //Stopping the uav
    prey.teardown();
}