#ifndef _MOTOR_MANAGER_H
#define _MOTOR_MANAGER_H

#include <Logger.h>

//TODO : the management should be different than Gyroscope and accelerometer regarding the management of the motor
//TODO : will be confirmed by the real class

/**
 * This class will handle the different motor present onboard.
 * The interface of this class will change for different aircraft (quadcopter, tricopter, plane, ...)
 */

class Motor_manager{

private:

    Logger &logger;

    /**
     * Values of the 4 motors of the quadcopter in percentage
     */
    float motor_x_m;
    float motor_x_p;
    float motor_y_m;
    float motor_y_p;



public:

    Motor_manager(Logger &logger);

    int init();

    int teardown();

    /**
     * Allow to control motors on a quadcopter
     * Speeds have to be set in percentage (0.0 : no speed - 100.0 full speed)
     */
    int set_motor_speed(float motor_x_m, float motor_x_p, float motor_y_m, float motor_y_p);

    /**
     * Allow to retrieve the speed previously set to the motors
     */
    void get_motor_speed(float &motor_x_m, float &motor_x_p, float &motor_y_m, float &motor_y_p);

};

#endif
