# Copyright: (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 2.6)
set(PROJECTNAME fakeRobot)
project(${PROJECTNAME})

find_package(YARP)

set(folder_source main.cpp)
source_group("Source Files" FILES ${folder_source})

include_directories(${fakeMotorDevice_INCLUDE_DIRS} ${YARP_INCLUDE_DIRS})
add_executable(${PROJECTNAME} ${folder_source})
target_link_libraries(${PROJECTNAME} fakeMotorDevice ${YARP_LIBRARIES})
install(TARGETS ${PROJECTNAME} DESTINATION ${TUTORIAL_INSTALL_DIR})

