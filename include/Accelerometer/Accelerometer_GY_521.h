#ifndef PREY_ACCELEROMETER_GY_521_H
#define PREY_ACCELEROMETER_GY_521_H

#include <Accelerometer.h>
#include <stdint.h>

#define GY_521_ADDRESS 0x68
#define CONFIG_REG 0x6B

/* Acceleration */
#define REG_ACCEL_X_HIGH 0x3B
#define REG_ACCEL_X_LOW 0x3C
#define REG_ACCEL_Y_HIGH 0x3D
#define REG_ACCEL_Y_LOW 0x3E
#define REG_ACCEL_Z_HIGH 0x3F
#define REG_ACCEL_Z_LOW 0x40

/* Sensitivity */
#define ACCEL_SENSITIVITY_2 16384.0
#define ACCEL_SENSITIVITY_4 8192.0
#define ACCEL_SENSITIVITY_8 4096.0
#define ACCEL_SENSITIVITY_16 2048.0

class Accelerometer_GY_521:public Accelerometer{

    //TODO : change
    double sensitivity = ACCEL_SENSITIVITY_2;
    int fd;

    int _init_accelerometer_sensor();

    int _teardown_accelerometer_sensor();

    double _get_x_acceleration();

    double _get_y_acceleration();

    double _get_z_acceleration();

    int16_t read_high_low_register(int8_t register_high, int8_t register_low);

public:
    using Accelerometer::Accelerometer;

};

#endif //PREY_ACCELEROMETER_GY_521_H