# Copyright: 2012 iCub Facility, Istituto Italiano di Tecnologia
# Author: Lorenzo Natale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

cmake_minimum_required(VERSION 3.5)
project(tutorial_arm_joint_impedance)

find_package(YARP)

add_executable(tutorial_arm_joint_impedance tutorial_arm_joint_impedance.cpp)
target_link_libraries(tutorial_arm_joint_impedance ${YARP_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
