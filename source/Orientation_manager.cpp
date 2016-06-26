#include <Orientation_manager.h>

Orientation_manager::Orientation_manager(){
    tilt = 0.0;
    pitch = 0.0;
    yaw = 0.0;
    update_frequency_ms = 0;
}


int Orientation_manager::init(int update_frequency_ms){
    this->update_frequency_ms = update_frequency_ms;
    orientation_manager_task = thread(&Orientation_manager::_main_task, this);
}

int Orientation_manager::get_orientation(double *tilt, double *pitch, double *yaw){
    *tilt = this->tilt;
    *pitch = this->pitch;
    *yaw = this->yaw;
}

int Orientation_manager::teardown(){
    orientation_manager_task.join();
}


void Orientation_manager::_main_task(){
    for(int i=0; i< 1000; i++){
        printf("Tilt : %f\n", tilt);
    }
}