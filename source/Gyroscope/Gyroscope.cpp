//
// Created by jaylesr on 27/06/16.
//

#include <Gyroscope.h>
#include <unistd.h>
#include <thread>
#include <mutex>

//Initialization of the static variable
mutex Gyroscope::gyroscope_lock;

Gyroscope::Gyroscope(Logger &logger): logger(logger){
    x_rotation_value = 0.0;
    y_rotation_value = 0.0;
    z_rotation_value = 0.0;
    update_frequency_ms = 0;
}

/**
 * Init the gyroscope class
 */
int Gyroscope::init(int update_frequency_ms){
    this->update_frequency_ms = update_frequency_ms;
    if(_init_gyroscope_sensor() == -1){
        //TODO replace by logger + custom error code
        logger.log(LOG_ERROR, "Error, impossible to init Gyroscope sensor");
        return -1;
    }

    /*If the values retrieved from the sensors have to be save for later simulations */
#ifdef SAVE_SENSORS_VALUES
    logger.log(LOG_DEBUG, "Creating the file for Accelerometer values");
    //Opening the file (
    save_file = fopen(SAVE_GYROSCOPE_FILENAME, "w+");
    //Registering the update frequency
    if(save_file == NULL){
        logger.log(LOG_ERROR, "Failing to open %s", SAVE_GYROSCOPE_FILENAME);
        return -1;
    }
    //First line is the update frequency
    fprintf(save_file, "%i\n", update_frequency_ms);
#endif

    run = true;
    this->update_frequency_ms = update_frequency_ms;
    gyroscope_task = thread(&Gyroscope::_main_task, this);


}

int Gyroscope::teardown(){
    int error_code;
    logger.log(LOG_INFO, "Teardown gyroscope");

    error_code = _teardown_gyroscope_sensor();
    if(error_code == -1)
        logger.log(LOG_ERROR, "Teardown gyroscope failed");

    logger.log(LOG_INFO, "Terminate Gyroscope thread");
    run = false;
    gyroscope_task.join();
    logger.log(LOG_INFO, "Gyroscope thread terminated");

#ifdef SAVE_SENSORS_VALUES
    logger.log(LOG_DEBUG, "Closing saving file");
    fclose(save_file);
#endif

    return error_code;
}

int Gyroscope::get_current_values(double *x_rotation_value, double *y_rotation_value, double *z_rotation_value){
    //mutex gyroscope_lock;
    gyroscope_lock.lock();
    *x_rotation_value = this->x_rotation_value;
    *y_rotation_value = this->y_rotation_value;
    *z_rotation_value = this->z_rotation_value;
    gyroscope_lock.unlock();
}

void Gyroscope::_main_task(){
    while(run){
        gyroscope_lock.lock();
        x_rotation_value = _get_x_rotation();
        y_rotation_value = _get_y_rotation();
        z_rotation_value = _get_z_rotation();

        /*If the values retrieved from the sensors have to be save for later simulations */
#ifdef SAVE_SENSORS_VALUES
        //Wrinting all the value retrieved from the file
        fprintf(save_file, "%f %f %f\n", x_rotation_value, y_rotation_value, z_rotation_value);
#endif

        gyroscope_lock.unlock();
        usleep(update_frequency_ms*1000);
    }
}

