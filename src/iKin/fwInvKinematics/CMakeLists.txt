# Copyright: 2010 RobotCub Consortium
# Author: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

cmake_minimum_required(VERSION 3.5)
project(fwInvKinematics)

find_package(YARP)
find_package(ICUB)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ICUB_MODULE_PATH})

if(NOT ICUB_USE_IPOPT)
    message(FATAL_ERROR "IPOPT is required")
endif()

set(folder_source main.cpp)
add_executable(${PROJECT_NAME} ${folder_source})
target_compile_definitions(${PROJECT_NAME} PRIVATE _USE_MATH_DEFINES)
target_link_libraries(${PROJECT_NAME} iKin ${YARP_LIBRARIES})
