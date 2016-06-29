cmake_minimum_required (VERSION 2.8.7)

project (prey)

find_package( Threads )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(include)
add_subdirectory (source)

file(COPY script/ DESTINATION script/)