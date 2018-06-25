# Copyright: 2012 iCub Facility, Istituto Italiano di Tecnologia
# Author: Lorenzo Natale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

cmake_minimum_required(VERSION 3.5)
project(motorControlImpedance)

find_package(YARP)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${YARP_MODULE_PATH})

add_executable(motorControlImpedance tutorial_arm_joint_impedance.cpp)
target_link_libraries(motorControlImpedance ${YARP_LIBRARIES})



