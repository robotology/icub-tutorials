# Copyright: 2012 iCub Facility, Istituto Italiano di Tecnologia
# Author: Lorenzo Natale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(PROJECTNAME module)
PROJECT(${PROJECTNAME})

find_package(YARP)

add_executable(module tutorial_module.cpp)
target_link_libraries(module ${YARP_LIBRARIES})






