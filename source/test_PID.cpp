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

#include <Orientation_manager.h>
#include <Flight_contoller.h>
#include <Motor_manager.h>
#include <Logger.h>

static bool run;
void handler(int v) {
    run = false;
}


int main(int argv, char **argc){
    return 0;
}

