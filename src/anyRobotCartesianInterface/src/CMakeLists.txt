# Copyright: (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.5)

add_subdirectory(fakeMotorDevice)

set(fakeMotorDevice_INCLUDE_DIRS ../fakeMotorDevice/include)
add_subdirectory(fakeRobot)
add_subdirectory(solver)
add_subdirectory(server)
add_subdirectory(client)

