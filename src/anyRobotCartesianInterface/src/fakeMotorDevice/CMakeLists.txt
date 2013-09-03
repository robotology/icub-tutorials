# Copyright: (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 2.6)
set(PROJECTNAME fakeMotorDevice)
project(${PROJECTNAME})

find_package(YARP)
find_package(ICUB)

set(folder_header include/fakeMotorDevice.h include/private/fakeMotorDeviceComponents.h)
set(folder_source src/fakeMotorDevice.cpp src/fakeMotorDeviceServer.cpp src/fakeMotorDeviceClient.cpp)

source_group("Header Files" FILES ${folder_header})
source_group("Source Files" FILES ${folder_source})

include_directories(${PROJECT_SOURCE_DIR}/include ${ICUB_INCLUDE_DIRS} ${YARP_INCLUDE_DIRS})
add_library(${PROJECTNAME} ${folder_source} ${folder_header})
target_link_libraries(${PROJECTNAME} ctrlLib ${YARP_LIBRARIES})
