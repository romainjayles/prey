#ifndef PREY_GYROSCOPE_GY_521_H
#define PREY_GYROSCOPE_GY_521_H

#include <Gyroscope.h>
#include <stdint.h>

#define GY_521_ADDRESS 0x68
#define CONFIG_REG 0x6B

#define GYRO_SENSITIVITY_250 131.0
#define GYRO_SENSITIVITY_500 65.5
#define GYRO_SENSITIVITY_1000 32.8
#define GYRO_SENSITIVITY_2000 16.4

/* Gyroscope */
#define REG_GYRO_X_HIGH 0x43
#define REG_GYRO_X_LOW 0x44
#define REG_GYRO_Y_HIGH 0x45
#define REG_GYRO_Y_LOW 0x46
#define REG_GYRO_Z_HIGH 0x47
#define REG_GYRO_Z_LOW 0x48


class Gyroscope_GY_521:public Gyroscope{

    int fd;
    double sensitivity;

    int _init_gyroscope_sensor();

    double _get_x_rotation();

    double _get_y_rotation();

    double _get_z_rotation();

    int16_t read_high_low_register(int8_t register_high, int8_t register_low);

public:
    using Gyroscope::Gyroscope;

};

#endif //PREY_GYROSCOPE_GY_521_H