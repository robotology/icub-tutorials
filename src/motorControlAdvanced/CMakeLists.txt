# Copyright: 2012 iCub Facility, Istituto Italiano di Tecnologia
# Author: Lorenzo Natale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(PROJECTNAME motorControlAdvanced)
PROJECT(${PROJECTNAME})

find_package(YARP)
find_package(iCub)

add_executable(tutorial_cartesian_interface tutorial_cartesian_interface.cpp)
target_link_libraries(tutorial_cartesian_interface ${YARP_LIBRARIES} icubmod)

add_executable(tutorial_gaze_interface tutorial_gaze_interface.cpp)
target_link_libraries(tutorial_gaze_interface ${YARP_LIBRARIES} icubmod)


