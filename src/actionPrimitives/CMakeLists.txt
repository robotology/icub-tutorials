# Copyright: 2015 iCub Facility - Istituto Italiano di Tecnologia
# Author: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.5)
project(tutorial_actionPrimitives)

find_package(YARP)
find_package(ICUB)

set(sources tutorial_actionPrimitives.cpp)
source_group("Source Files" FILES ${sources})

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} perceptiveModels
                                      actionPrimitives
                                      ${YARP_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

file(GLOB conf ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/*.ini)
yarp_install(FILES ${conf} DESTINATION actionPrimitives)
