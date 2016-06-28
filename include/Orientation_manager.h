//
// Created by jaylesr on 24/06/16.
//


#ifndef PREY_ORIENTATION_MANAGER_H
#define PREY_ORIENTATION_MANAGER_H

#include <Orientation_manager.h>
#include <Gyroscope_GY_521.h>
#include <Accelerometer_GY_521.h>
#include <thread>

using namespace std;

class Orientation_manager
{
private:

    /**
     * The latest values of the orientation of the UAV
     */
    double tilt;
    double pitch;
    double yaw;

    /**
     * The update frequency of the tilt, pitch, yaw
     */
    int update_frequency_ms;

    //Accelerometer accelerometer;
    Gyroscope_GY_521 gyroscope;
    Accelerometer_GY_521 accelerometer;
    thread orientation_manager_task;

public:
    Orientation_manager();

    /**
     * Allow to init the class and its atributes
     *
     */
    int init(int update_frequency_ms);

    /**
     * Get the buffer computed by the thread
     */
    int get_orientation(double *tilt, double *pitch, double *yaw);

    /**
     * Properly stop the class and the thread
     */
    int teardown();

private:
    /**
     * This is the main thread of the class
     * It will calculate the actual orientation based on the sensors values
     */
    void _main_task();

};




#endif //PREY_ORIENTATION_MANAGER_H
