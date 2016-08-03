#include <Accelerometer_GY_521.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int Accelerometer_GY_521::_init_accelerometer_sensor(){

    fd = wiringPiI2CSetup(GY_521_ADDRESS);
    if(fd == -1){
        logger.log(LOG_ERROR, "Can't setup the I2C device for gy_521\n");
        return -1;
    }
    //See the manual, but we put the sleep mode at 0
    logger.log(LOG_INFO, "I2C set up successfully\n");
    logger.log(LOG_DEBUG, "Config : %x\n", wiringPiI2CReadReg8(fd, CONFIG_REG));
    wiringPiI2CWriteReg8(fd, CONFIG_REG, 0);
    logger.log(LOG_INFO, "Setup success\n");
    return 0;
}

double Accelerometer_GY_521::_get_x_acceleration(){
    return read_high_low_register(REG_ACCEL_X_HIGH, REG_ACCEL_X_LOW)/sensitivity;
}

double Accelerometer_GY_521::_get_y_acceleration(){
    return read_high_low_register(REG_ACCEL_Y_HIGH, REG_ACCEL_Y_LOW)/sensitivity;
}

double Accelerometer_GY_521::_get_z_acceleration(){
    return read_high_low_register(REG_ACCEL_Z_HIGH, REG_ACCEL_Z_LOW)/sensitivity;
}

int16_t Accelerometer_GY_521::read_high_low_register(int8_t register_high, int8_t register_low){
    int16_t value = 0;
    value = wiringPiI2CReadReg8(fd, register_high);
    value = (value << 8) | wiringPiI2CReadReg8(fd, register_low);
    return value;
}