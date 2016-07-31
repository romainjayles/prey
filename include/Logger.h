//
// Created by jaylesr on 29/07/16.
//

#ifndef PREY_LOGGER_H
#define PREY_LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <mutex>

using namespace std;

#define MAX_FILENAME_SIZE 512

typedef enum {
    LOG_ERROR = 0,
    LOG_INFO = 1,
    LOG_DEBUG = 2,
    LOG_NONE = 3
}log_level;

/**
 * Class used to centralized logging message
 * Implemented as a singleton
 */
class Logger{

private:
    char log_filename[MAX_FILENAME_SIZE+1];
    log_level current_log_level;

    static mutex logger_lock;
public:

    /**
     * log_level : The desired threshold for reporting the log message
     * log_filename : The file to log the message
     */
    Logger(log_level level, char* log_filename = NULL);

    /* The two lasts arguments are used to init the logger */
    void log(char* log_message, log_level actual_log);

};
#endif //PREY_LOGGER_H
