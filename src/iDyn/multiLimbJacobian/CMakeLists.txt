# Copyright: 2010-2011 RobotCub Consortium
# Author: Serena Ivaldi
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 
cmake_minimum_required(VERSION 3.5)

project(multiLimbJacobian)

find_package(YARP)
find_package(ICUB)

set(folder_source main.cpp)
add_executable(${PROJECT_NAME} ${folder_source})
target_compile_definitions(${PROJECT_NAME} PRIVATE _USE_MATH_DEFINES)
target_link_libraries(${PROJECT_NAME} ctrlLib iKin skinDynLib iDyn ${YARP_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)