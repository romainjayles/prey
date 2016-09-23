//
// Created by jaylesr on 23/09/16.
//

#ifndef _GPS_MOCK_H_
#define _GPS_MOCK_H_

#include <GPS.h>

class GPS_mock:public GPS{

    virtual int _init_GPS_sensor();

    virtual int _teardown_GPS_sensor();

    /**
     * Fill the class attributes latitude, longitude, altitude with the correct values
     */
    virtual int _get_GPS_values();

public:

    using GPS::GPS;
};

#endif //_GPS_MOCK_H_
