# Copyright: 2015 iCub Facility - Istituto Italiano di Tecnologia
# Author: Lorenzo Natale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 2.6)
set(PROJECTNAME rpcIdl)
project(${PROJECTNAME})

find_package(YARP)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})

include(YarpIDL)
yarp_idl_to_dir(IRpcServer.thrift ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB header_files include/*.h)
file(GLOB source_files src/*.cpp)
file(GLOB idl_files *.thrift)
set(doc_files ${PROJECTNAME}.xml)

source_group("Header Files" FILES ${header_files})
source_group("Source Files" FILES ${source_files})
source_group("IDL Files"    FILES ${idl_files})
source_group("DOC Files"    FILES ${doc_files})

include_directories(${PROJECT_SOURCE_DIR}/include ${YARP_INCLUDE_DIRS})
add_executable(${PROJECTNAME} ${header_files} ${source_files} ${idl_files} ${doc_files})
target_link_libraries(${PROJECTNAME} ${YARP_LIBRARIES})
