/**
 * This class will handle the correct orientation of the uav
 * It receive order from other class and send command to the motors to reach the desired goal
 *
 */

#ifndef _FLIGHT_CONTROLLER_
#define _FLIGHT_CONTROLLER_

#include <Logger.h>
#include <Orientation_manager.h>
#include <Motor_manager.h>
#include <thread>

class Flight_controller{

private:

    float desired_roll;
    float desired_pitch;
    float desired_yaw;

    float previous_roll_error;
    float previous_pitch_error;
    float previous_yaw_error;

    int roll_precision;
    int pitch_precision;
    int yaw_precision;

    Logger &logger;
    Orientation_manager orientation_manager;
    Motor_manager motor_manager;

    /**
     * The update frequency of the main thread
     */
    int update_frequency_ms;

    static mutex flight_controller_lock;
    thread flight_controller_task;
    bool run;

public:

    Flight_controller(Logger &logger);

    /**
     * To init the flight controller
     */
    int init(int update_frequency_ms);

    /**
     * Allow to teardown the flight controller
     */
    int teardown();

    /**
    * Allow to command the pitch
    * desired_pitch : the desired angle
    * precision : the input - output tolerance
    */
    int command_pitch(float desired_pitch, int precision);

    /**
    * Allow to command the roll
    * desired_roll : the desired angle
    * precision : the input - output tolerance
    */
    int command_roll(float desired_roll, int precision);


    /**
    * Allow to command the yaw
    * desired_yaw : the desired angle
    * precision : the input - output tolerance
    */
    int command_yaw(float desired_yaw, int precision);

    /**
     * The main task of the class, will be threaded
     */
    void _main_task();

};

#endif