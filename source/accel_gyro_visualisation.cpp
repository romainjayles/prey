//
// Created by jaylesr on 30/06/16.
//
/*
 * Used to output the acceleration and gyroscope values, for debug use
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#ifdef MOCK
#include <Accelerometer_GY_521_mock.h>
#include <Gyroscope_GY_521_mock.h>
#else
#include <Accelerometer_GY_521.h>
#include <Gyroscope_GY_521.h>
#endif


static bool run;
void handler(int v) {
    run = false;
}


int main(int argv, char **argc){
    int update;
    signal(SIGINT, handler);
    Logger logger(LOG_INFO);

    #ifdef MOCK
    Accelerometer_GY_521_mock accelerometer = Accelerometer_GY_521_mock(logger);
    Gyroscope_GY_521_mock gyroscope = Gyroscope_GY_521_mock(logger);
    #else
    Accelerometer_GY_521 accelerometer = Accelerometer_GY_521(logger);
    Gyroscope_GY_521 gyroscope = Gyroscope_GY_521(logger);
    #endif


    double accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z;
    if(argv != 2){
        printf("Error, the update frequency of measurement should be specified in argument\n");
    }else{
        update = atoi(argc[1]);
        if(accelerometer.init(update) == -1)
            return -1;

        if(gyroscope.init(update) == -1)
            return -1;

        run = true;
        while(run){
            accelerometer.get_current_values(&accel_x, &accel_y, &accel_z);
            gyroscope.get_current_values(&gyro_x, &gyro_y, &gyro_z);
            printf("%f %f %f %f %f %f\n", accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z);
            usleep(update*1000);
        }
        accelerometer.teardown();
        gyroscope.teardown();
    }
    return 0;
}