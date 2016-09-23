//
// Created by jaylesr on 23/09/16.
//

#include <GPS_mock.h>

int GPS_mock::_init_GPS_sensor(){
    //TODO : DO
    return 0;
}

int GPS_mock::_teardown_GPS_sensor(){
    //TODO : DO
    return 0;
}

/**
 * Fill the class attributes latitude, longitude, altitude with the correct values
 */
int GPS_mock::_get_GPS_values(){
    latitude = 1.1;
    longitude = 2.2;
    altitude = 3.3;
    return 0;
}
