# Copyright: (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.5)
project(anyRobotCartesianInterface)

find_package(YARP 3.5.1 REQUIRED)
find_package(ICUB)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Installation directory" FORCE)

add_subdirectory(src)
add_subdirectory(app)

