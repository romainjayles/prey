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

static bool run;
void handler(int v) {
    run = false;
}


int main(int argv, char **argc){
    int update;
    signal(SIGINT, handler);
    Logger logger(LOG_ERROR);

    float roll, pitch, yaw;

    Orientation_manager orientation_manager(logger);
    if(argv != 2){
        printf("Error, the update frequency of measurement should be specified in argument\n");
    }else{
        update = atoi(argc[1]);
        if(orientation_manager.init(update) == -1)
            return -1;


        run = true;
        while(run){
            orientation_manager.get_orientation(&roll, &pitch, &yaw);
            logger.log(LOG_INFO, "%f %f %f\n", roll, pitch, yaw);
            usleep(update*1000);
        }
        orientation_manager.teardown();
    }
    return 0;
}
