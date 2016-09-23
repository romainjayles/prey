cmake_minimum_required (VERSION 2.8.7)

project (prey)

find_package( Threads )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)
include_directories(include/Accelerometer)
include_directories(include/Gyroscope)
include_directories(include/Barometer)
include_directories(include/GPS)

add_subdirectory (source)
add_subdirectory (source/Gyroscope)
add_subdirectory (source/Accelerometer)
add_subdirectory (source/GPS)
add_subdirectory (source/Barometer)

file(COPY script/ DESTINATION script/)