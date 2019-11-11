# Copyright: 2010-2011 RobotCub Consortium
# Author: Serena Ivaldi
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(oneChainWithSensor)

FIND_PACKAGE(YARP)
FIND_PACKAGE(ICUB)

SET(folder_source main.cpp)
ADD_EXECUTABLE(${PROJECT_NAME} ${folder_source})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} skinDynLib iDyn ${YARP_LIBRARIES})
INSTALL(TARGETS ${PROJECT_NAME} DESTINATION bin)