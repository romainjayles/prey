//
// Created by jaylesr on 24/06/16.
//

#ifndef PREY_CONFIG_H
#define PREY_CONFIG_H

//#define SAVE_SENSORS_VALUES

#define SAVE_ACCELEROMETER_FILENAME "accelerometer_saving"
#define SAVE_GYROSCOPE_FILENAME "gyroscope_saving"

/**
 * Logging constant
 */

#define MAX_FILENAME_SIZE 512
#define MAX_LOG_MESSAGE_SIZE 512
#define MAX_LOAD_FROM_FILE_LINE_SIZE 512

/*
 * Multithreading related constant
 */

#define FLIGHT_CONTROLLER_UPDATE_FREQUENCY_MS 50
#define GYROSCOPE_UPDATE_FREQUENCY_MS 50
#define ACCELEROMETER_UPDATE_FREQUENCY_MS 50
#define GPS_UPDATE_FREQUENCY_MS 100
#define BAROMETER_UPDATE_FREQUENCY 100

#define ORIENTATION_MANAGER_UPDATE_FREQUENCY_MS 50


/**
 * PID related constant
 */

#define KP_ROLL 1.0
#define KD_ROLL 1.0
#define KI_ROLL 1.0

#define KP_PITCH 1.0
#define KD_PITCH 1.0
#define KI_PITCH 1.0

#define KP_YAW 1.0
#define KD_YAW 1.0
#define KI_YAW 1.0

#endif //PREY_CONFIG_H
