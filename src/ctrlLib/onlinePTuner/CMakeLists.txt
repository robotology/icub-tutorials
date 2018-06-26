# Copyright: (C) 2012 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.5)
project(onlinePTuner)

find_package(YARP)
find_package(ICUB)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ICUB_MODULE_PATH})

set(folder_source main.cpp)
add_executable(${PROJECT_NAME} ${folder_source})
target_link_libraries(${PROJECT_NAME} ctrlLib ${YARP_LIBRARIES})
