# Copyright: 2012 iCub Facility, Istituto Italiano di Tecnologia
# Author: Lorenzo Natale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

cmake_minimum_required(VERSION 3.5)
project(motorControlAdvanced)

find_package(YARP)

add_executable(tutorial_cartesian_interface tutorial_cartesian_interface.cpp)
target_compile_definitions(tutorial_cartesian_interface PRIVATE _USE_MATH_DEFINES)
target_link_libraries(tutorial_cartesian_interface ${YARP_LIBRARIES})

add_executable(tutorial_gaze_interface tutorial_gaze_interface.cpp)
target_compile_definitions(tutorial_gaze_interface PRIVATE _USE_MATH_DEFINES)
target_link_libraries(tutorial_gaze_interface ${YARP_LIBRARIES})
