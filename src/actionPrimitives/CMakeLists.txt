# Copyright: 2015 iCub Facility - Istituto Italiano di Tecnologia
# Author: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.5)
set(PROJECTNAME tutorial_actionPrimitives)
project(${PROJECTNAME})

find_package(YARP)
find_package(ICUB)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH}
                              ${ICUB_MODULE_PATH})

set(sources tutorial_actionPrimitives.cpp)
source_group("Source Files" FILES ${sources})

add_executable(${PROJECTNAME} ${sources})
target_link_libraries(${PROJECTNAME} perceptiveModels
                                     actionPrimitives
                                     ${YARP_LIBRARIES})

########## application
include(YarpInstallationHelpers)

file(GLOB conf ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/*.ini)
yarp_install(FILES ${conf} DESTINATION actionPrimitives)
