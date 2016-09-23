//
// Created by jaylesr on 23/09/16.
//

#include <GPS.h>
#include <unistd.h>

//Initialization of the static variable
mutex GPS::GPS_lock;

GPS::GPS(Logger &logger): logger(logger){
    latitude = 0.0;
    longitude = 0.0;
    altitude = 0.0;
}

int GPS::init(int update_frequency_ms){ ;
    if(_init_GPS_sensor() == -1){
        logger.log(LOG_ERROR, "Error, Impossible to init GPS sensor");
        return -1;
    }
    this->update_frequency_ms = update_frequency_ms;
    run = true;
    GPS_task = thread(&GPS::_main_task, this);

};

int GPS::teardown(){
    int error_code;
    logger.log(LOG_INFO, "Teardown GPS");

    error_code = _teardown_GPS_sensor();
    if(error_code == -1)
        logger.log(LOG_ERROR, "Teardown GPS failed");

    logger.log(LOG_INFO, "Terminate GPS thread");
    run = false;
    GPS_task.join();
    logger.log(LOG_INFO, "GPS thread terminated");
    return error_code;

}

int GPS::get_current_values(float *latitude, float *longitude, float *altitude){
    GPS_lock.lock();
    *latitude = this->latitude;
    *longitude = this->longitude;
    *altitude = this->altitude;
    GPS_lock.unlock();
}

void GPS::_main_task(){
    while(run){
        GPS_lock.lock();
        //Class members latitude, longitude, altitude will be modified
        if(_get_GPS_values()){
            logger.log(LOG_ERROR, "Error while retrieving GPS values");
        }
        GPS_lock.unlock();
        logger.log(LOG_DEBUG, "GPS : %f %f %f", longitude, latitude, longitude);
        usleep(update_frequency_ms*1000);
    }
}