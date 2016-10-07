#ifndef PREY_GYROSCOPE_GY_521_MOCK_H
#define PREY_GYROSCOPE_GY_521_MOCK_H

#include <Gyroscope.h>
#include <config.h>

class Gyroscope_GY_521_mock:public Gyroscope{

    FILE *save_file;

    int _init_gyroscope_sensor();

    int _teardown_gyroscope_sensor();

    float _get_x_rotation();

    float _get_y_rotation();

    float _get_z_rotation();

    /**
     * Allow to load the values directly from a file
     * It can manage values refreshment when needed
     * this function can't be common between gyroscope and accelerometer values because of static values
     */
    int load_from_file(float *buffer, axis axis_desired);

public:
    using Gyroscope::Gyroscope;

};

#endif //PREY_GYROSCOPE_GY_521_MOCK_H