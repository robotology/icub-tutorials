# Copyright: (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 2.6)
set(PROJECTNAME server)
project(${PROJECTNAME})

find_package(YARP)
find_package(ICUB)

set(folder_source main.cpp)
source_group("Source Files" FILES ${folder_source})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ICUB_LINK_FLAGS}")

include_directories(${fakeMotorDevice_INCLUDE_DIRS} ${ICUB_INCLUDE_DIRS} ${YARP_INCLUDE_DIRS})
add_executable(${PROJECTNAME} ${folder_source})
target_link_libraries(${PROJECTNAME} fakeMotorDevice icubmod ${YARP_LIBRARIES})
install(TARGETS ${PROJECTNAME} DESTINATION bin)


