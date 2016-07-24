#ifndef PREY_GYROSCOPE_GY_521_H
#define PREY_GYROSCOPE_GY_521_H

#include <Gyroscope.h>
#include <stdint.h>

class Gyroscope_GY_521:public Gyroscope{

    int _init_gyroscope_sensor();

    double _get_x_rotation();

    double _get_y_rotation();

    double _get_z_rotation();

};

#endif //PREY_GYROSCOPE_GY_521_H