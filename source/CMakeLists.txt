
#If we want to mock the hardware part with custom class (maybe not the best way to do)
if(MOCK)
    add_definitions(-DMOCK)
    set(executable_dep ${executable_dep} Accelerometer/Accelerometer_GY_521_mock.cpp Gyroscope/Gyroscope_GY_521_mock.cpp)
else(NOT MOCK)
    find_package(WiringPi REQUIRED)

    include_directories(${WIRINGPI_INCLUDE_DIRS})
    set(executable_dep ${executable_dep} Accelerometer/Accelerometer_GY_521.cpp Gyroscope/Gyroscope_GY_521.cpp)
endif()

set(executable_dep ${executable_dep} Prey.cpp Orientation_manager.cpp Gyroscope/Gyroscope.cpp  Accelerometer/Accelerometer.cpp Logger.cpp)

add_executable(uav_prey main.cpp ${executable_dep})
add_executable(accel_gyro_visualisation accel_gyro_visualisation.cpp ${executable_dep})

target_link_libraries( uav_prey ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( accel_gyro_visualisation ${CMAKE_THREAD_LIBS_INIT} )

if (NOT MOCK)
    target_link_libraries( uav_prey ${WIRINGPI_LIBRARIES})
    target_link_libraries( accel_gyro_visualisation ${WIRINGPI_LIBRARIES})
endif ()