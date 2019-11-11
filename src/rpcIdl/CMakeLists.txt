# Copyright: 2015 iCub Facility - Istituto Italiano di Tecnologia
# Author: Lorenzo Natale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.5)
project(rpcIdl)

find_package(YARP)

yarp_idl_to_dir(INPUT_FILES IRpcServer.thrift OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB header_files include/*.h)
file(GLOB source_files src/*.cpp)
file(GLOB idl_files *.thrift)
set(doc_files ${PROJECT_NAME}.xml)

source_group("Header Files" FILES ${header_files})
source_group("Source Files" FILES ${source_files})
source_group("IDL Files"    FILES ${idl_files})
source_group("DOC Files"    FILES ${doc_files})

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME} ${header_files} ${source_files} ${idl_files} ${doc_files})
target_link_libraries(${PROJECT_NAME} ${YARP_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
