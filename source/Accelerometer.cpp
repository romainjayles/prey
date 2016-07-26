//
// Created by jaylesr on 28/06/16.
//

#include <Accelerometer.h>
#include <unistd.h>
#include <thread>
#include <mutex>


//Initialization of the static variable
mutex Accelerometer::accelerometer_lock;

Accelerometer::Accelerometer() {
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
        printf("Error, impossible to init Accelerometer sensor\n");
        return -1;
    }
    accelerometer_task = thread(&Accelerometer::_main_task, this);
    return 0;
}

int Accelerometer::teardown() {
    //stop
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
    while (true) {
        //printf("Accel\n");
        accelerometer_lock.lock();
        x_acceleration_value = _get_x_acceleration();
        y_acceleration_value = _get_y_acceleration();
        z_acceleration_value = _get_z_acceleration();
        accelerometer_lock.unlock();
        usleep(update_frequency_ms * 1000);
    }
}


