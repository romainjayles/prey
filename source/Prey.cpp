//
// Created by jaylesr on 20/06/16.
//

#include <Prey.h>
#include <Orientation_manager.h>
#include <config.h>

#include <stdio.h>

Prey::Prey(){
    current_state = SLEEPING;
}

int Prey::init(){
    orientation_manager = Orientation_manager();
    orientation_manager.init(ORIENTATION_MANAGER_UPDATE_FREQUENCY_MS);
    printf("Test !!!");
}

int Prey::teardown(){
    orientation_manager.teardown();
}
