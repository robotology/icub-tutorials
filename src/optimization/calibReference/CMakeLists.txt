# Copyright: (C) 2012 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.5)
project(calibReference)

find_package(YARP)
find_package(ICUB)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${YARP_MODULE_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ICUB_MODULE_PATH})

if(NOT ICUB_USE_IPOPT)
    message(FATAL_ERROR "IPOPT is required")
endif()

set(folder_source main.cpp)
source_group("Source Files" FILES ${folder_source})

add_definitions(-D_USE_MATH_DEFINES)
add_executable(${PROJECT_NAME} ${folder_source})
target_link_libraries(${PROJECT_NAME} optimization ${YARP_LIBRARIES})


