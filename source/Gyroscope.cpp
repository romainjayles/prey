//
// Created by jaylesr on 27/06/16.
//

#include <Gyroscope.h>
#include <unistd.h>

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
    //TODO add mutexes
    *x_rotation_value = this->x_rotation_value;
    *y_rotation_value = this->y_rotation_value;
    *z_rotation_value = this->z_rotation_value;
}

void Gyroscope::_main_task(){
    while(true){
        printf("Gyro\n");
        usleep(update_frequency_ms*1000);
    }
}

