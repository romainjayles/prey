#include <Gyroscope_GY_521_mock.h>

int Gyroscope_GY_521_mock::_init_gyroscope_sensor(){

    size_t len = 0;
    char *update_string = NULL;

    logger.log(LOG_DEBUG, "Opening the file for Gyroscope values");
    //Opening the file (
    save_file = fopen(SAVE_GYROSCOPE_FILENAME, "r");
    //Registering the update frequency
    if(save_file == NULL){
        logger.log(LOG_ERROR, "Failing to open %s", SAVE_GYROSCOPE_FILENAME);
        return -1;
    }
    // If the first line is empty
    if(getline(&update_string, &len, save_file) == -1){
        logger.log(LOG_ERROR, "Gyroscope save file is empty");
        return -1;
    }

    // We test if the save file has been save with the same update frequency
    if(atoi(update_string) != update_frequency_ms){
        logger.log(LOG_ERROR, "\"Error the file has been recorded at %ims, %ims is not a correct update value\"", atoi(update_string), update_frequency_ms);
        return -1;
    }
    logger.log(LOG_DEBUG, "Gyroscope successfully mocked");
    free(update_string);
    return 0;
}

int Gyroscope_GY_521_mock::_teardown_gyroscope_sensor(){
    int error_code = 0;
    if(fclose(save_file))
        error_code = -1;

    return error_code;
}


double Gyroscope_GY_521_mock::_get_x_rotation(){
    double value = 0.0;
    load_from_file(&value, AXIS_X);
    return value;
}

double Gyroscope_GY_521_mock::_get_y_rotation(){
    double value = 0.0;
    load_from_file(&value, AXIS_Y);
    return value;
}

double Gyroscope_GY_521_mock::_get_z_rotation(){
    double value = 0.0;
    load_from_file(&value, AXIS_Z);
    return value;
}

/**
 * Allow to load the values directly from a file
 * It can manage values refreshment when needed
 * this function can't be common between gyroscope and gyroscope values because of static values
 */
int Gyroscope_GY_521_mock::load_from_file(double *buffer, axis axis_desired){
    static bool x_new = true;
    static bool y_new = true;
    static bool z_new = true;
    static double x_value = 0.0;
    static double y_value = 0.0;
    static double z_value = 0.0;
    double values_array[3];
    char *values = NULL;
    size_t len;
    // If the value has already been fetched, we must triger a new line reading
    if( (axis_desired == AXIS_X && !x_new) || (axis_desired == AXIS_Y && !y_new) || (axis_desired == AXIS_Z && !z_new)){
        if(getline(&values, &len, save_file) == -1){
            free(values);
            logger.log(LOG_ERROR, "File %s empty", SAVE_GYROSCOPE_FILENAME);
            return -1;
        }
        // We then get extract decimal values separated by space from the string
        int j=0;
        int previous_index = 0;
        for(int i=0; values[i] != '\0'; i++){
            // if we have found a separator;
            if(values[i] == ' '){
                values[i] = '\0';
                values_array[j] = atof(&values[previous_index]);
                j++;
                //The begining of the next value in the string
                previous_index = i+1;
            }
        }
        values_array[j] = atof(&values[previous_index]);
        x_value = values_array[0];
        y_value = values_array[1];
        z_value = values_array[2];
        x_new = true;
        y_new = true;
        z_new = true;
    }

    // We return the value demanded and turn the associated new flag to false
    switch (axis_desired){
        case AXIS_X:
            *buffer = x_value;
            x_new = false;
            break;
        case AXIS_Y:
            *buffer = y_value;
            y_new = false;
            break;
        case AXIS_Z:
            z_new = false;
            *buffer = z_value;
            break;
    }
    free(values);
    return 0;
}