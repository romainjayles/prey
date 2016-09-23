/**
 * This is the main entry point of the application
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <Prey.h>
#include <Logger.h>

#define MAIN_SLEEP_MS 3000

/**
 * Used to handle the Ctrl-C and terminate the application
 */
static bool run;
void handler(int v) {
    run = false;
}

/**
 * This is the main entry point of the program,
 * It will take care of interfacing the user's will with the uav actions
 */
int main(int argv, char **argc){

    run = true;
    signal(SIGINT, handler);
    
    Logger logger(LOG_NONE);
    //Creation of the main interface class
    Prey prey(logger);
    //Initialization of the uav
    prey.init();
    while(run)
        usleep(5000);
    //Stopping the uav
    prey.teardown();
}