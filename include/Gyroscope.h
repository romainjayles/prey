//
// Created by jaylesr on 24/06/16.
//

#ifndef PREY_GYROSCOPE_H
#define PREY_GYROSCOPE_H

class Gyroscope{
protected:

    /**
     * The last value acquired
     */
    double x_rotation_value;
    double y_rotation_value;
    double z_rotation_value;


    int update_frequency_ms; //The refresh time of gyroscope values

    /**
     *
     */
    virtual int _init_gyroscope_sensor();

    virtual double _get_x_rotation();

    virtual double _get_y_rotation();

    virtual double _get_z_rotation();

public:
    Gyroscope(int update_frequency_ms);

    /**
     * Init the gyroscope class
     */
    int init();

    int get_x_value(double *value);

    int get_y_value(double *value);

    int get_z_value(double *value);




};

#endif //PREY_GYROSCOPE_H
