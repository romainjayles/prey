#include <Gyroscope_GY_521.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>


int Gyroscope_GY_521::_init_gyroscope_sensor(){
    fd = wiringPiI2CSetup(GY_521_ADDRESS);
    if(fd == -1){
        logger.log(LOG_ERROR, "Can't setup the I2C device for gy_521\n");
        return -1;
    }
    //See the manual, but we put the sleep mode at 0
    logger.log(LOG_INFO, "I2C set up successfully\n");
    logger.log(LOG_DEBUG, "Config : %x\n", wiringPiI2CReadReg8(fd, CONFIG_REG));
    wiringPiI2CWriteReg8(fd, CONFIG_REG, 0);
    sensitivity = GYRO_SENSITIVITY_250;
    wiringPiI2CWriteReg8(fd, 0x1B, 0);
    logger.log(LOG_INFO, "Setup success\n");
    return 0;
}

int Gyroscope_GY_521::_teardown_gyroscope_sensor(){
    return 0;
}

float Gyroscope_GY_521::_get_x_rotation(){
    return read_high_low_register(REG_GYRO_X_HIGH, REG_GYRO_X_LOW)/sensitivity;
}

float Gyroscope_GY_521::_get_y_rotation(){
    return read_high_low_register(REG_GYRO_Y_HIGH, REG_GYRO_Y_LOW)/sensitivity;
}

float Gyroscope_GY_521::_get_z_rotation(){
    return read_high_low_register(REG_GYRO_Z_HIGH, REG_GYRO_Z_LOW)/sensitivity;
}

int16_t Gyroscope_GY_521::read_high_low_register(int8_t register_high, int8_t register_low){
    int16_t value = 0;
    value = wiringPiI2CReadReg8(fd, register_high);
    value = (value << 8) | wiringPiI2CReadReg8(fd, register_low);
    return value;
}

