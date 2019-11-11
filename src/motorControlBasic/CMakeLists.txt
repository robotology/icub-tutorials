# Copyright: 2012 iCub Facility, Istituto Italiano di Tecnologia
# Author: Lorenzo Natale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

cmake_minimum_required(VERSION 3.5)
project(motorControlBasic)

find_package(YARP)

add_executable(tutorial_arm tutorial_arm.cpp)
target_link_libraries(tutorial_arm ${YARP_LIBRARIES})
install(TARGETS tutorial_arm DESTINATION bin)
