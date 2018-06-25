# Copyright: (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.5)
project(solver)

find_package(YARP)
find_package(ICUB)
list(APPEND CMAKE_MODULE_PATH ${ICUB_MODULE_PATH})
include(iCubOptions)

if(NOT ICUB_USE_IPOPT)
   message(FATAL_ERROR "${PROJECT_NAME}: IPOPT is strictly required!")
endif()

set(folder_source main.cpp)
source_group("Source Files" FILES ${folder_source})

include_directories(${fakeMotorDevice_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${folder_source})
target_link_libraries(${PROJECT_NAME} fakeMotorDevice iKin ${YARP_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)


