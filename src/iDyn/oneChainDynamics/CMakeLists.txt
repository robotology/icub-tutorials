# Copyright: 2010-2011 RobotCub Consortium
# Author: Serena Ivaldi
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(oneChainDynamics)

FIND_PACKAGE(YARP)
FIND_PACKAGE(ICUB)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ICUB_MODULE_PATH})

SET(folder_source main.cpp)
ADD_EXECUTABLE(${PROJECT_NAME} ${folder_source})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} iDyn ${YARP_LIBRARIES})
