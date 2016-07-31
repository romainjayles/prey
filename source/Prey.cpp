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
    printf("Launching orientation manager\n");
    orientation_manager = Orientation_manager();
    orientation_manager.init(ORIENTATION_MANAGER_UPDATE_FREQUENCY_MS);
}

int Prey::teardown(){
    printf("Terminate Prey\n");
    orientation_manager.teardown();
    printf("Prey terminated\n");
}
