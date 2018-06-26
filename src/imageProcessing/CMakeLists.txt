# Copyright: 2012 iCub Facility, Istituto Italiano di Tecnologia
# Author: Lorenzo Natale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(imageProcessing)

find_package(YARP)

add_executable(findLocation findLocation.cpp)
target_link_libraries(findLocation ${YARP_LIBRARIES})

add_executable(lookAtLocation lookAtLocation.cpp)
target_link_libraries(lookAtLocation ${YARP_LIBRARIES})
