//
// Created by jaylesr on 30/06/16.
//
/*
 * Used to output the acceleration and gyroscope values, for debug use
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef MOCK
#include <Accelerometer_GY_521_mock.h>
#include <Gyroscope_GY_521_mock.h>
#else
#include <Accelerometer_GY_521.h>
#include <Gyroscope_GY_521.h>
#endif


int main(int argv, char **argc){
    int update;

    #ifdef MOCK
    Accelerometer_GY_521_mock accelerometer = Accelerometer_GY_521_mock();
    Gyroscope_GY_521_mock gyroscope = Gyroscope_GY_521_mock();
    #else
    Accelerometer_GY_521 accelerometer = Accelerometer_GY_521();
    Gyroscope_GY_521 gyroscope = Gyroscope_GY_521();
    #endif


    double accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z;
    if(argv != 2){
        printf("Error, the update frequency of measurement should be specified in argument\n");
    }else{
        update = atoi(argc[1]);
        accelerometer.init(update);
        gyroscope.init(update);
        while(true){
            accelerometer.get_current_values(&accel_x, &accel_y, &accel_z);
            gyroscope.get_current_values(&gyro_x, &gyro_y, &gyro_z);
            printf("%f %f %f %f %f %f\n", accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z);
            usleep(update*1000);
        }
    }
    return 0;
}