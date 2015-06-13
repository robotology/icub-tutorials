cmake_minimum_required(VERSION 2.8.9)

set(PROJECTNAME tutorials)

project(${PROJECTNAME})

find_package(YARP REQUIRED)
find_package(ICUB REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${YARP_MODULE_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ICUB_MODULE_PATH})
include(iCubOptions)

include_directories(${ICUB_INCLUDE_DIRS} ${YARP_INCLUDE_DIRS})

## this is for testing only, please ignore if you are reading tutorials	
include(CTest)
### end test specific code

# go by subdirectories
add_subdirectory(imageProcessing)
add_subdirectory(module)
add_subdirectory(motorControlBasic)
add_subdirectory(motorControlAdvanced)
add_subdirectory(rateThread)
add_subdirectory(ctrlLib)
add_subdirectory(iDyn)
add_subdirectory(learningMachines)
add_subdirectory(perceptiveModels)
add_subdirectory(actionPrimitives)

#set(ICUB_USE_GSL "ON" CACHE BOOL "dependency flag" FORCE)
#set(ICUB_USE_GLUT "ON" CACHE BOOL "dependency flag" FORCE)
#set(ICUB_USE_OpenGL "ON" CACHE BOOL "dependency flag" FORCE)
#set(ICUB_USE_ODE "ON" CACHE BOOL "dependency flag" FORCE)
#set(ICUB_USE_SDL "ON" CACHE BOOL "dependency flag" FORCE)
#set(ICUB_USE_GtkMM "ON" CACHE BOOL "dependency flag" FORCE)
#set(ICUB_USE_GtkPlus "ON" CACHE BOOL "dependency flag" FORCE)
#set(ICUB_USE_Gthread "ON" CACHE BOOL "dependency flag" FORCE)
#set(ICUB_USE_ACE "ON" CACHE BOOL "dependency flag" FORCE)
#set(ICUB_USE_IPOPT "ON" CACHE BOOL "dependency flag" FORCE)
#set(ICUB_USE_IPP "OFF" CACHE BOOL "dependency flag" FORCE)
#set(ICUB_USE_OpenCV "ON" CACHE BOOL "dependency flag" FORCE)
#set(ICUB_USE_Qt3 "ON" CACHE BOOL "dependency flag" FORCE)

if(ICUB_USE_OpenCV)
    find_package(OpenCV QUIET)
    message(STATUS "Testing iCubVis dependent code")

    add_executable(test_icubVis smoke-tests/icubVis.cpp)
    target_link_libraries(test_icubVis ${YARP_LIBRARIES} iCubVis)

    ### execute tests
    add_test(NAME test_icubVis COMMAND test_icubVis)
else()
    message(STATUS "OpenCV not found")
endif()

if(ICUB_USE_IPOPT)
    find_package(IPOPT QUIET)
    message(STATUS "Testing IPOPT dependent code")

    add_executable(test_ipopt smoke-tests/ipopt.cpp)
    target_link_libraries(test_ipopt ${YARP_LIBRARIES} iKin)

    ### execute tests
    add_test(NAME test_ipopt COMMAND test_ipopt)
    add_subdirectory(iKin)
    add_subdirectory(optimization)
else()
    message(STATUS "IPOPT not found")
endif()

###################### end of test specific code

