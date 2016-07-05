//
// Created by jaylesr on 27/06/16.
//

#include <Gyroscope.h>
#include <unistd.h>
#include <thread>
#include <mutex>

//Initialization of the static variable
mutex Gyroscope::gyroscope_lock;

Gyroscope::Gyroscope(){
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
    gyroscope_task = thread(&Gyroscope::_main_task, this);
}

int Gyroscope::teardown(){
    //stop
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
    while(true){
        //printf("Gyro\n");
        gyroscope_lock.lock();
        x_rotation_value = _get_x_rotation();
        y_rotation_value = _get_y_rotation();
        z_rotation_value = _get_z_rotation();
        gyroscope_lock.unlock();
        usleep(update_frequency_ms*1000);
    }
}

