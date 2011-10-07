# Copyright: (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 2.6)
set(PROJECTNAME anyRobotCartesianInterface)
project(${PROJECTNAME})

find_package(ICUB)
set(CMAKE_MODULE_PATH ${ICUB_MODULE_PATH} ${CMAKE_MODULE_PATH})
include(iCubHelpers)

set(ICUB_APPLICATIONS_PREFIX "${CMAKE_SOURCE_DIR}/bin"  CACHE PATH "Application path prefix")

add_subdirectory(src)
add_subdirectory(app)

