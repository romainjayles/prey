//
// Created by jaylesr on 24/06/16.
//


#ifndef PREY_ORIENTATION_MANAGER_H
#define PREY_ORIENTATION_MANAGER_H

#include <Logger.h>
#include <thread>
#ifdef MOCK
#include <Gyroscope_GY_521_mock.h>
#include <Accelerometer_GY_521_mock.h>
#else
#include <Gyroscope_GY_521.h>
#include <Accelerometer_GY_521.h>
#endif

using namespace std;

class Orientation_manager
{
private:

    Logger &logger;

    /**
     * The latest values of the orientation of the UAV
     */
    double pitch;
    double roll;
    double yaw;

    /**
     * The update frequency of the tilt, pitch, yaw
     */
    int update_frequency_ms;

    //Accelerometer accelerometer;
    #ifdef MOCK
    Gyroscope_GY_521_mock gyroscope;
    Accelerometer_GY_521_mock accelerometer;
    #else
    Gyroscope_GY_521 gyroscope;
    Accelerometer_GY_521 accelerometer;
    #endif
    static mutex orientation_manager_lock;
    thread orientation_manager_task;
    bool run;

public:
    Orientation_manager(Logger &logger);

    /**
     * Allow to init the class and its atributes
     *
     */
    int init(int update_frequency_ms);

    /**
     * Get the buffer computed by the thread
     */
    int get_orientation(double *pitch, double *roll, double *yaw);

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
