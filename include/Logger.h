//
// Created by jaylesr on 29/07/16.
//

#ifndef PREY_LOGGER_H
#define PREY_LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <mutex>

#include <config.h>
using namespace std;



typedef enum {
    LOG_TEST = -1,
    LOG_ERROR = 0,
    LOG_INFO = 1,
    LOG_DEBUG = 2,
    LOG_NONE = 3
}log_level;

/**
 * Class used to centralized logging message
 */
class Logger{

private:
    char log_filename[MAX_FILENAME_SIZE+1];
    char logger_buffer[MAX_LOG_MESSAGE_SIZE];
    log_level current_log_level;

    static mutex logger_lock;
public:

    /**
     * log_level : The desired threshold for reporting the log message
     * log_filename : The file to log the message
     */
    Logger(log_level level, char* log_filename = NULL);

    /* The two lasts arguments are used to init the logger */
    void log(log_level message_level, const char* log_message, ...);

};
#endif //PREY_LOGGER_H
