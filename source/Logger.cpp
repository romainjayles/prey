//
// Created by jaylesr on 29/07/16.
//

#include <Logger.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <mutex>


mutex Logger::logger_lock;

Logger::Logger(log_level level, char* log_filename){
    current_log_level = level;
    if(log_filename != NULL && strlen(log_filename) > MAX_FILENAME_SIZE) {
        printf("Warning filename too long to be stored into the buffer, messages will not be logged inside %s",
                   log_filename);
        log_filename = NULL;
    }
    if(log_filename != NULL)
        strcpy(this->log_filename, log_filename);
}

void Logger::log(log_level message_level, const char* log_message, ...){
    va_list args;
    //TODO : add file logging and thread safe ?
    if(message_level <= current_log_level){
        logger_lock.lock();
        va_start(args, log_message);
        vsnprintf(logger_buffer, MAX_LOG_MESSAGE_SIZE, log_message, args);
        va_end(args);
        printf("%s\n", logger_buffer);
        logger_lock.unlock();
    }

}
