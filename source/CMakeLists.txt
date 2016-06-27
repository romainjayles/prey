

add_executable(uav_prey main.cpp Prey.cpp Orientation_manager.cpp Gyroscope.cpp Gyroscope_GY_521.cpp)

target_link_libraries( uav_prey ${CMAKE_THREAD_LIBS_INIT} )