#include <Gyroscope_GY_521_mock.h>

int Gyroscope_GY_521_mock::_init_gyroscope_sensor(){
    return 0;
}

double Gyroscope_GY_521_mock::_get_x_rotation(){
    return 1.0;
}

double Gyroscope_GY_521_mock::_get_y_rotation(){
    return 2.0;
}

double Gyroscope_GY_521_mock::_get_z_rotation(){
    return 3.0;
}