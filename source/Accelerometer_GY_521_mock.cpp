#include <Accelerometer_GY_521_mock.h>

int Accelerometer_GY_521_mock::_init_accelerometer_sensor(){
    return 0;
}

double Accelerometer_GY_521_mock::_get_x_acceleration(){
    return 11.0;
}

double Accelerometer_GY_521_mock::_get_y_acceleration(){
    return 22.0;
}

double Accelerometer_GY_521_mock::_get_z_acceleration(){
    return 33.0;
}
