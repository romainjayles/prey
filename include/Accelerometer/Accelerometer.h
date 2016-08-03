//
// Created by jaylesr on 24/06/16.
//

#ifndef PREY_ACCELEROMETER_H
#define PREY_ACCELEROMETER_H

#include <Logger.h>
#include <config.h>

#include <thread>
#include <mutex>

//#define SAVE_SENSORS_VALUES

using namespace std;

class Accelerometer{
protected:

    Logger &logger;

    /*If the values retrieved from the sensors have to be save for later simulations */
#ifdef SAVE_SENSORS_VALUES
    FILE *save_file = NULL;
#endif
    /**
     * The last value acquired
     */
    double x_acceleration_value;
    double y_acceleration_value;
    double z_acceleration_value;


    int update_frequency_ms; //The refresh time of accelerometer values

    /**
     * The interface to the real implementation
     */
    virtual int _init_accelerometer_sensor() = 0;

    virtual double _get_x_acceleration() = 0;

    virtual double _get_y_acceleration() = 0;

    virtual double _get_z_acceleration() = 0;

    thread accelerometer_task;
    bool run;
    static mutex accelerometer_lock;

public:
    explicit Accelerometer(Logger &logger);

    /**
     * The copy method (used for threading purpose)
     */


    /**
     * Init the accelerometer class
     */
    int init(int update_frequency_ms);

    int teardown();

    int get_current_values(double *x_acceleration_value, double *y_acceleration_value, double *z_acceleration_value);

    void _main_task();


};

#endif //PREY_ACCELEROMETER_H
