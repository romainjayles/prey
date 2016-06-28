#ifndef PREY_ACCELEROMETER_GY_521_H
#define PREY_ACCELEROMETER_GY_521_H

#include <Accelerometer.h>

class Accelerometer_GY_521:public Accelerometer{

    int _init_accelerometer_sensor();

    double _get_x_acceleration();

    double _get_y_acceleration();

    double _get_z_acceleration();

};

#endif //PREY_ACCELEROMETER_GY_521_H