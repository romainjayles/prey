

add_executable(uav_prey main.cpp Prey.cpp Orientation_manager.cpp Gyroscope.cpp Gyroscope_GY_521.cpp Accelerometer.cpp Accelerometer_GY_521.cpp)
add_executable(accel_gyro_visualisation accel_gyro_visualisation Gyroscope.cpp Gyroscope_GY_521.cpp Accelerometer.cpp Accelerometer_GY_521.cpp)

target_link_libraries( uav_prey ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( accel_gyro_visualisation ${CMAKE_THREAD_LIBS_INIT} )