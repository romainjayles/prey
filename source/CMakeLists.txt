#set(MOCK OFF)

set(executable_list ${executable_list} Prey.cpp Orientation_manager.cpp Gyroscope.cpp  Accelerometer.cpp)

#If we want to mock the hardware part with custom class
if(MOCK)
    add_definitions(-DMOCK)
    set(executable_list ${executable_list} Accelerometer_GY_521_mock.cpp Gyroscope_GY_521_mock.cpp)
else(NOT MOCK)
    set(executable_list ${executable_list} Accelerometer_GY_521.cpp Gyroscope_GY_521.cpp)
endif()


add_executable(uav_prey main.cpp ${executable_list})
add_executable(accel_gyro_visualisation accel_gyro_visualisation.cpp ${executable_list})

target_link_libraries( uav_prey ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( accel_gyro_visualisation ${CMAKE_THREAD_LIBS_INIT} )