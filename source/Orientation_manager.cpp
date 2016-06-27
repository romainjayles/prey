#include <Orientation_manager.h>
#include <Gyroscope_GY_521.h>
#include <config.h>
#include <unistd.h>


Orientation_manager::Orientation_manager(){
    tilt = 0.0;
    pitch = 0.0;
    yaw = 0.0;
    update_frequency_ms = 0;
}

int Orientation_manager::init(int update_frequency_ms){
    this->update_frequency_ms = update_frequency_ms;
    // We launch the accelerometer with the right update value
    //accelerometer = Accelerometer();
    gyroscope = Gyroscope_GY_521();
    //accelerometer.init(ACCELEROMETER_UPDATE_FREQUENCY_MS);
    gyroscope.init(GYROSCOPE_UPDATE_FREQUENCY_MS);
    orientation_manager_task = thread(&Orientation_manager::_main_task, this);
}

int Orientation_manager::get_orientation(double *tilt, double *pitch, double *yaw){
    *tilt = this->tilt;
    *pitch = this->pitch;
    *yaw = this->yaw;
}

int Orientation_manager::teardown(){
    //TODO : join ?
    gyroscope.teardown();
    orientation_manager_task.join();
}


void Orientation_manager::_main_task(){
    while(true){
        printf("Tilt : %f\n", tilt);
        usleep(update_frequency_ms*1000);
    }

}