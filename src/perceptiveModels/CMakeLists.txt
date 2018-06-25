# Copyright: 2015 iCub Facility - Istituto Italiano di Tecnologia
# Author: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.5)
project(tutorial_perceptiveModels)

find_package(YARP)
find_package(ICUB)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH}
                              ${ICUB_MODULE_PATH})

set(sources tutorial_perceptiveModels.cpp)
source_group("Source Files" FILES ${sources})

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} perceptiveModels ${YARP_LIBRARIES})
