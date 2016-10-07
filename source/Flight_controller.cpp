#include <Flight_controller.h>
#include <Motor_manager.h>
#include <Logger.h>
#include <unistd.h>

//Initialization of the static variable
mutex Flight_controller::flight_controller_lock;

Flight_controller::Flight_controller(Logger &logger):logger(logger), orientation_manager(logger), motor_manager(logger){
    desired_pitch = 0.0;
    desired_yaw = 0.0;
    desired_roll = 0.0;

    roll_precision = 0;
    pitch_precision = 0;
    yaw_precision = 0;

    //TODO be sure that this initialisation is legit
    previous_roll_error = 0.0;
    previous_pitch_error = 0.0;
    previous_yaw_error = 0.0;

}

/**
 * To init the flight controller
 */
int Flight_controller::init(int update_frequency_ms){
    this->update_frequency_ms = update_frequency_ms;

    // Launching the task necessary for flight_controller
    logger.log(LOG_INFO, "Launching orientation manager");
    orientation_manager.init(ORIENTATION_MANAGER_UPDATE_FREQUENCY_MS);
    motor_manager.init();

    // Launching the flight controllerN
    run = true;
    flight_controller_task = thread(&Flight_controller::_main_task, this);
    return 0;
}

/**
 * Allow to teardown the flight controller
 */
int Flight_controller::teardown(){
    orientation_manager.teardown();
    motor_manager.teardown();

    run = false;
    flight_controller_task.join();

    logger.log(LOG_INFO, "Flight Controller task terminated");
    return 0;
}

/**
* Allow to command the pitch
* desired_pitch : the desired angle
* precision : the input - output tolerance
*/
int Flight_controller::command_pitch(float desired_pitch, int precision){
    flight_controller_lock.lock();
    this->desired_pitch = desired_pitch;
    this->pitch_precision = precision;
    flight_controller_lock.unlock();
}

/**
* Allow to command the roll
* desired_roll : the desired angle
* precision : the input - output tolerance
*/
int Flight_controller::command_roll(float desired_roll, int precision){
    flight_controller_lock.lock();
    this->desired_roll = desired_roll;
    this->roll_precision = precision;
    flight_controller_lock.unlock();
}


/**
* Allow to command the yaw
* desired_yaw : the desired angle
* precision : the input - output tolerance
*/
int Flight_controller::command_yaw(float desired_yaw, int precision){
    flight_controller_lock.lock();
    this->desired_yaw = desired_yaw;
    this->yaw_precision = precision;
    flight_controller_lock.unlock();
}

/**
 * This is the main task of the Flight Controller
 * It will receives the informations on the orientation and the desired orientation
 * It will command the motors in order to fit the command
 */
void Flight_controller::_main_task(){
    float roll_error, pitch_error, yaw_error;
    while(run){
        flight_controller_lock.lock();
        //TODO : add integral error
        //TODO : check if the update_frequency_ms is actually respected between 2 calls
        logger.log(LOG_ERROR, "Not implemented yet");

        //TODO find the right scale to adapt the output from the PID to [0-100]
        flight_controller_lock.unlock();

        // We save the current error for re-use
        previous_roll_error = roll_error;
        previous_pitch_error = pitch_error;
        previous_yaw_error = yaw_error;

        usleep(update_frequency_ms*1000);
    }

}
