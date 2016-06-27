/**
 * This is the main entry point of the application
 */


#include <stdio.h>
#include <stdlib.h>

#include <Prey.h>

/**
 * This is the main entry point of the program,
 * It will take care of interfacing the user's will with the uav actions
 */
int main(int argv, char **argc){
    printf("Launching ...\n");
    //Creation of the main interface class
    Prey prey;
    //Initialization of the uav
    prey.init();
    printf(".. end");
    //Stopping the uav
    prey.teardown();
}