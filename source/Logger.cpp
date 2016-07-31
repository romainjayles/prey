//
// Created by jaylesr on 29/07/16.
//

#include <Logger.h>
#include <stdio.h>
#include <stdlib.h>
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

void Logger::log(char* log_message, log_level message_level){
    //TODO : add file logging and thread safe ?
    if(message_level <= current_log_level){
        logger_lock.lock();
        printf("%s\n", log_message);
        logger_lock.unlock();
    }

}
