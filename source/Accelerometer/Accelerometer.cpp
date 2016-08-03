//
// Created by jaylesr on 28/06/16.
//

#include <Accelerometer.h>
#include <unistd.h>
#include <thread>
#include <mutex>


//Initialization of the static variable
mutex Accelerometer::accelerometer_lock;

Accelerometer::Accelerometer(Logger &logger): logger(logger) {
    x_acceleration_value = 0.0;
    y_acceleration_value = 0.0;
    z_acceleration_value = 0.0;
    update_frequency_ms = 0;
}

/**
 * Init the accelerometer class
 */
int Accelerometer::init(int update_frequency_ms) {
    this->update_frequency_ms = update_frequency_ms;
    if(_init_accelerometer_sensor() == -1){
        //TODO replace by logger + custom error code
        logger.log(LOG_ERROR, "Error, impossible to init Accelerometer sensor");
        return -1;
    }

/*If the values retrieved from the sensors have to be save for later simulations */
#ifdef SAVE_SENSORS_VALUES
    logger.log(LOG_DEBUG, "Creating the file for Accelerometer values");
    //Opening the file (
    save_file = fopen(SAVE_ACCELEROMETER_FILENAME, "w+");
    //Registering the update frequency
    if(save_file == NULL){
        logger.log(LOG_ERROR, "Failing to open %s", SAVE_ACCELEROMETER_FILENAME);
        return -1;
    }
    //First line is the update frequency
    fprintf(save_file, "%i\n", update_frequency_ms);
#endif
    run = true;
    accelerometer_task = thread(&Accelerometer::_main_task, this);
    return 0;
}

int Accelerometer::teardown() {
    logger.log(LOG_INFO, "Terminate Accelerometer thread");
    run = false;
    accelerometer_task.join();
    logger.log(LOG_INFO, "Accelerometer thread terminated");

#ifdef SAVE_SENSORS_VALUES
    logger.log(LOG_DEBUG, "Closing saving file");
    fclose(save_file);
#endif
}

int Accelerometer::get_current_values(double *x_acceleration_value, double *y_acceleration_value, double *z_acceleration_value) {
    //mutex accelerometer_lock;
    accelerometer_lock.lock();
    *x_acceleration_value = this->x_acceleration_value;
    *y_acceleration_value = this->y_acceleration_value;
    *z_acceleration_value = this->z_acceleration_value;
    accelerometer_lock.unlock();
}

void Accelerometer::_main_task() {
    while (run) {
        accelerometer_lock.lock();
        x_acceleration_value = _get_x_acceleration();
        y_acceleration_value = _get_y_acceleration();
        z_acceleration_value = _get_z_acceleration();

/*If the values retrieved from the sensors have to be save for later simulations */
#ifdef SAVE_SENSORS_VALUES
        //Wrinting all the value retrieved from the file
        fprintf(save_file, "%f %f %f\n", x_acceleration_value, y_acceleration_value, z_acceleration_value);
#endif
        accelerometer_lock.unlock();
        usleep(update_frequency_ms * 1000);
    }
}


