# Copyright: 2012 iCub Facility, Istituto Italiano di Tecnologia
# Author: Lorenzo Natale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

cmake_minimum_required(VERSION 2.6)
project(motorControlAdvanced)

find_package(YARP)
find_package(ICUB)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH ${ICUB_MODULE_PATH})

include_directories(${ICUB_INCLUDE_DIRS} ${YARP_INCLUDE_DIRS})

# import math symbols from standard cmath
add_definitions(-D_USE_MATH_DEFINES)

add_executable(tutorial_cartesian_interface tutorial_cartesian_interface.cpp)
target_link_libraries(tutorial_cartesian_interface ${YARP_LIBRARIES})

add_executable(tutorial_gaze_interface tutorial_gaze_interface.cpp)
target_link_libraries(tutorial_gaze_interface ${YARP_LIBRARIES})


