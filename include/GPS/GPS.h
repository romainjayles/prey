//
// Created by jaylesr on 23/09/16.
//

#ifndef _GPS_H_
#define _GPS_H_

#include <Logger.h>
#include <config.h>
#include <utils.h>


#include <thread>
#include <mutex>

class GPS{

protected:

    /**
     * Values retrieved by the GPS
     */
    float latitude;
    float longitude;
    float altitude;

    Logger logger;


    virtual int _init_GPS_sensor() = 0;

    virtual int _teardown_GPS_sensor() = 0;

    /**
     * Fill the class attributes latitude, longitude, altitude with the correct values
     */
    virtual int _get_GPS_values() = 0;

    int update_frequency_ms;
    thread GPS_task;
    bool run;
    static mutex GPS_lock;

public:

    explicit GPS(Logger &logger);

    /**
     * The visible part of the interface
     */

    int init(int update_frequency_ms);

    int teardown();

    int get_current_values(float *latitude, float *longitude, float *altitude);

private:

    void _main_task();
};

#endif //_GPS_H_
