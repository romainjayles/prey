//
// Created by jaylesr on 24/06/16.
//

#ifndef PREY_GYROSCOPE_H
#define PREY_GYROSCOPE_H

#include <Logger.h>

#include <thread>
#include <mutex>

using namespace std;

class Gyroscope{
protected:

    Logger &logger;

    /**
     * The last value acquired
     */
    double x_rotation_value;
    double y_rotation_value;
    double z_rotation_value;


    int update_frequency_ms; //The refresh time of gyroscope values

    /**
     * The interface to the real implementation
     */
    virtual int _init_gyroscope_sensor() = 0;

    virtual double _get_x_rotation() = 0;

    virtual double _get_y_rotation() = 0;

    virtual double _get_z_rotation() = 0;

    thread gyroscope_task;
    bool run;
    static mutex gyroscope_lock;

public:
    explicit Gyroscope(Logger &logger);

    /**
     * The copy method (used for threading purpose)
     */


    /**
     * Init the gyroscope class
     */
    int init(int update_frequency_ms);

    int teardown();

    int get_current_values(double *x_rotation_value, double *y_rotation_value, double *z_rotation_value);

    void _main_task();


};

#endif //PREY_GYROSCOPE_H