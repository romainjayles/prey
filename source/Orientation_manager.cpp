#include <Orientation_manager.h>
#include <Logger.h>
#include <config.h>
#include <math.h>
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
    pitch = 0.0;
    roll = 0.0;
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

int Orientation_manager::get_orientation(double *pitch, double *roll, double *yaw){
    orientation_manager_lock.lock();
    *pitch = this->pitch;
    *roll = this->roll;
    *yaw = this->yaw;
    orientation_manager_lock.unlock();
}

int Orientation_manager::teardown(){
    logger.log(LOG_INFO, "Terminate Orientation_manager thread");
    accelerometer.teardown();
    gyroscope.teardown();
    run = false;
    orientation_manager_task.join();
    logger.log(LOG_INFO, "Orientation_manager thread terminated");
}


void Orientation_manager::_main_task(){
    double pitch_accel, roll_accel, pitch_gyro, roll_gyro, current_pitch, current_roll;
    double accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z;
    double ratio = 0.1;


    while(run){
        accelerometer.get_current_values(&accel_x, &accel_y, &accel_z);
        gyroscope.get_current_values(&gyro_x, &gyro_y, &gyro_z);

        orientation_manager_lock.lock();

        pitch_gyro = this->pitch + gyro_y*update_frequency_ms/1000.0;
        roll_gyro = this->roll + gyro_x*update_frequency_ms/1000.0;

        roll_accel = atan2(accel_y, accel_z) * 180/M_PI, 360;
        pitch_accel = atan2(-accel_x, sqrt(accel_y*accel_y + accel_z*accel_z)) * 180/M_PI;

        this->pitch = (1-ratio)*pitch_gyro + ratio*pitch_accel;
        this->roll = (1-ratio)*roll_gyro + ratio*roll_accel;

        logger.log(LOG_TEST, "TEST_ORIENTATION::%f %f %f", roll, pitch, yaw);

        orientation_manager_lock.unlock();
        usleep(update_frequency_ms*1000);
    }

}