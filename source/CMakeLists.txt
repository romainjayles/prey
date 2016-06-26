

add_executable(uav_prey main.cpp Prey.cpp Orientation_manager.cpp)

target_link_libraries( uav_prey ${CMAKE_THREAD_LIBS_INIT} )