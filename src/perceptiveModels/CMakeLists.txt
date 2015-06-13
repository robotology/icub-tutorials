# Copyright: 2015 iCub Facility - Istituto Italiano di Tecnologia
# Author: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 2.6)
set(PROJECTNAME tutorial_perceptiveModels)
project(${PROJECTNAME})

find_package(YARP)
find_package(ICUB)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH}
                              ${ICUB_MODULE_PATH})

set(sources tutorial_perceptiveModels.cpp)
source_group("Source Files" FILES ${sources})

include_directories(${perceptiveModels_INCLUDE_DIRS} ${YARP_INCLUDE_DIRS})
add_executable(${PROJECTNAME} ${sources})
target_link_libraries(${PROJECTNAME} perceptiveModels ${YARP_LIBRARIES})
