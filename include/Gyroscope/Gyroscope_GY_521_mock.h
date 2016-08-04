#ifndef PREY_GYROSCOPE_GY_521_MOCK_H
#define PREY_GYROSCOPE_GY_521_MOCK_H

#include <Gyroscope.h>
#include <config.h>

class Gyroscope_GY_521_mock:public Gyroscope{

    FILE *save_datas;

    int _init_gyroscope_sensor();

    double _get_x_rotation();

    double _get_y_rotation();

    double _get_z_rotation();

public:
    using Gyroscope::Gyroscope;

};

#endif //PREY_GYROSCOPE_GY_521_MOCK_H