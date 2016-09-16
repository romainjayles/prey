#include <Motor_manager.h>
#include <Logger.h>


Motor_manager::Motor_manager(Logger &logger): logger(logger){
    float motor_s = 0.0;
    float motor_n = 0.0;
    float motor_e = 0.0;
    float motor_w = 0.0;
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

int Motor_manager::set_motor_speed(float motor_s, float motor_n, float motor_e, float motor_w){
    logger.log(LOG_INFO, "MOTOR MANAGER SPEED SET AT : %f, %f, %f, %f", motor_s, motor_n, motor_e, motor_w);
    this->motor_s = motor_s;
    this->motor_n = motor_n;
    this->motor_e = motor_e;
    this->motor_w = motor_w;

    //TODO : the real management

}

void Motor_manager::get_motor_speed(float &motor_s, float &motor_n, float &motor_e, float &motor_w){
    motor_s = this->motor_s;
    motor_n = this->motor_n;
    motor_e = this->motor_e;
    motor_w = this->motor_w;
}

