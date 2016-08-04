#ifndef PREY_ACCELEROMETER_GY_521_MOCK_H
#define PREY_ACCELEROMETER_GY_521_MOCK_H

#include <Accelerometer.h>
#include <config.h>

/**
 *
 * This class allow to mock the accelerometer from previous recorded datas
 */

class Accelerometer_GY_521_mock:public Accelerometer{

    FILE *save_file;

    int _init_accelerometer_sensor();

    double _get_x_acceleration();

    double _get_y_acceleration();

    double _get_z_acceleration();

    /**
     * Allow to load the values directly from a file
     * It can manage values refreshment when needed
     * this function can't be common between gyroscope and accelerometer values because of static values
     */
    int load_from_file(double *buffer, axis axis_desired);

public:
    using Accelerometer::Accelerometer;

};

#endif //PREY_ACCELEROMETER_GY_521_MOCK_H