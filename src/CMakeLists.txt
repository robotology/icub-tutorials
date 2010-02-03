IF(WIN32)
cmake_minimum_required(VERSION 2.6)
ELSE(WIN32)
cmake_minimum_required(VERSION 2.4)
ENDIF(WIN32)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

SET(PROJECTNAME tutorials)

PROJECT(tutorials)

FIND_PACKAGE(YARP)
FIND_PACKAGE(ICUB)

FIND_PACKAGE(icubmod)
IMPORT_DEVICES(${ICUB_DIR}/tutorials/src/drivers.h icubmod)

# Find .cpp and .h files automatically.  This is a bit lazy,
# and in principle it would be better to list these files manually.
FILE(GLOB folder_source *.cpp)
FILE(GLOB folder_header *.h)

# Declare groups of source and header files -- makes things pretty in MSVC.

# Create everything needed to build our executable.
ADD_EXECUTABLE(imageProc imageProc.cpp)
ADD_EXECUTABLE(findLocation findLocation.cpp)
ADD_EXECUTABLE(lookAtLocation lookAtLocation.cpp)
ADD_EXECUTABLE(relay relay.cpp)
ADD_EXECUTABLE(tutorial_arm tutorial_arm.cpp)
ADD_EXECUTABLE(tutorial_rf_basic tutorial_rf_basic.cpp)
ADD_EXECUTABLE(tutorial_rf_advanced tutorial_rf_advanced.cpp)
ADD_EXECUTABLE(tutorial_rate_thread tutorial_rate_thread.cpp)
ADD_EXECUTABLE(tutorial_module tutorial_module.cpp)
ADD_EXECUTABLE(tutorial_cartesian_interface tutorial_cartesian_interface.cpp)


