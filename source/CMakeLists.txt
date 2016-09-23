
#If we want to mock the hardware part with custom class (maybe not the best way to do)
if(MOCK)
    add_definitions(-DMOCK)
    set(executable_common_dep ${executable_common_dep} Accelerometer/Accelerometer_GY_521_mock.cpp Gyroscope/Gyroscope_GY_521_mock.cpp GPS/GPS_mock.cpp)
else(NOT MOCK)
    find_package(WiringPi REQUIRED)

    include_directories(${WIRINGPI_INCLUDE_DIRS})
    set(executable_common_dep ${executable_common_dep} Accelerometer/Accelerometer_GY_521.cpp Gyroscope/Gyroscope_GY_521.cpp)
endif()

set(executable_common_dep ${executable_common_dep}
        Prey.cpp
        Flight_controller.cpp
        Motor_manager.cpp
        Orientation_manager.cpp
        Gyroscope/Gyroscope.cpp
        Accelerometer/Accelerometer.cpp
        Logger.cpp
        Barometer/Barometer.cpp
        GPS/GPS.cpp)

set(uav_prey_dep ${executable_common_dep})
set(accel_gyro_visualisation_dep ${executable_common_dep})
set(orientation_visualisation_dep ${executable_common_dep})

add_executable(uav_prey main.cpp ${uav_prey_dep})
add_executable(accel_gyro_visualisation accel_gyro_visualisation.cpp ${accel_gyro_visualisation_dep})
add_executable(orientation_visualisation orientation_visualisation.cpp ${orientation_visualisation_dep})

target_link_libraries( uav_prey ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( accel_gyro_visualisation ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( orientation_visualisation ${CMAKE_THREAD_LIBS_INIT} )

if (NOT MOCK)
    target_link_libraries( uav_prey ${WIRINGPI_LIBRARIES})
    target_link_libraries( accel_gyro_visualisation ${WIRINGPI_LIBRARIES})
    target_link_libraries( orientation_visualisation ${WIRINGPI_LIBRARIES})
endif ()