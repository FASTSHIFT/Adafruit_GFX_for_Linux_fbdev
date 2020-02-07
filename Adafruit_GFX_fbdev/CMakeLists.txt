
cmake_minimum_required(VERSION 3.5)

project(Adafruit_GFX_fbdev)

add_definitions(-D ARDUINO=111)

include_directories(
    "ArduinoAPI"
    "Libraries"
)

file(GLOB_RECURSE SOURCES 
    "main.cpp"
    "ArduinoAPI/*.c"
    "ArduinoAPI/*.cpp"
    "Libraries/Adafruit_GFX_Library/*.cpp"
    "Libraries/fbdev/*.cpp"
)

add_executable(ada_fb ${SOURCES})

set(CMAKE_BUILD_TYPE "Release")

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno -unused -variable -pthread")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
 	set(CMAKE_BUILD_TYPE "Release")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -pthread -fopenmp")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

message("Build Type:" ${CMAKE_BUILD_TYPE} ${CMAKE_CXX_FLAGS})
