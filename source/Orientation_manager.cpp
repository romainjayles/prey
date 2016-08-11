#include <Orientation_manager.h>
#include <Logger.h>
#include <config.h>
#include <unistd.h>

#ifdef MOCK
#include <Gyroscope_GY_521_mock.h>
#include <Accelerometer_GY_521_mock.h>
#else
#include <Gyroscope_GY_521.h>
#include <Accelerometer_GY_521.h>
#endif

//Initialization of the static variable
mutex Orientation_manager::orientation_manager_lock;


Orientation_manager::Orientation_manager(Logger &logger): logger(logger), accelerometer(logger), gyroscope(logger){
    tilt = 0.0;
    pitch = 0.0;
    yaw = 0.0;
    update_frequency_ms = 0;
}

int Orientation_manager::init(int update_frequency_ms){
    this->update_frequency_ms = update_frequency_ms;
    // We launch the accelerometer and gyroscope with the right update frequency
    if(accelerometer.init(ACCELEROMETER_UPDATE_FREQUENCY_MS) == -1)
        return -1;

    if(gyroscope.init(GYROSCOPE_UPDATE_FREQUENCY_MS) == -1)
        return -1;

    run = true;
    orientation_manager_task = thread(&Orientation_manager::_main_task, this);
}

int Orientation_manager::get_orientation(double *tilt, double *pitch, double *yaw){
    orientation_manager_lock.lock();
    *tilt = this->tilt;
    *pitch = this->pitch;
    *yaw = this->yaw;
    orientation_manager_lock.unlock();
}

int Orientation_manager::teardown(){
    logger.log(LOG_INFO, "Terminate orientation_manager thread");
    accelerometer.teardown();
    gyroscope.teardown();
    run = false;
    orientation_manager_task.join();
    logger.log(LOG_INFO, "orientation_manager thread terminated");
}


void Orientation_manager::_main_task(){
    while(run){
        orientation_manager_lock.lock();
        tilt++;
        pitch++;
        yaw++;
        orientation_manager_lock.unlock();
        usleep(update_frequency_ms*1000);
    }

}