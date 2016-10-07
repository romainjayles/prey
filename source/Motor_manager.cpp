#include <Motor_manager.h>
#include <Logger.h>


Motor_manager::Motor_manager(Logger &logger): logger(logger){
    float motor_x_m = 0.0;
    float motor_x_p = 0.0;
    float motor_y_m = 0.0;
    float motor_y_p = 0.0;
}

int Motor_manager::init(){
    logger.log(LOG_INFO, "MOTOR MANAGER INIT");
    return 0;
    //TODO : the real init
}

int Motor_manager::teardown(){
    logger.log(LOG_INFO, "MOTOR MANAGER TEARDOWN");
    return 0;
    //TODO : the real teardown
}

int Motor_manager::set_motor_speed(float motor_x_m, float motor_x_p, float motor_y_m, float motor_y_p){
    logger.log(LOG_INFO, "MOTOR MANAGER SPEED SET AT : %f, %f, %f, %f", motor_x_m, motor_x_p, motor_y_m, motor_y_p);
    this->motor_x_m = motor_x_m;
    this->motor_x_p = motor_x_p;
    this->motor_y_m = motor_y_m;
    this->motor_y_p = motor_y_p;

    //TODO : the real management

}

void Motor_manager::get_motor_speed(float &motor_x_m, float &motor_x_p, float &motor_y_m, float &motor_y_p){
    motor_x_m = this->motor_x_m;
    motor_x_p = this->motor_x_p;
    motor_y_m = this->motor_y_m;
    motor_y_p = this->motor_y_p;
}

