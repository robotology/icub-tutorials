CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(PROJECTNAME tutorials)

PROJECT(${PROJECTNAME})

FIND_PACKAGE(YARP)
FIND_PACKAGE(ICUB)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${YARP_MODULE_PATH})
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ICUB_MODULE_PATH})
INCLUDE(iCubOptions)

INCLUDE_DIRECTORIES(${ICUB_INCLUDE_DIRS}
                    ${YARP_INCLUDE_DIRS})

## this is for testing only, please ignore if you are reading tutorials	
INCLUDE(CTest)
### end test specific code

# go by subdirectories
add_subdirectory(imageProcessing)
add_subdirectory(module)
add_subdirectory(motorControlBasic)
add_subdirectory(motorControlAdvanced)
add_subdirectory(rateThread)
add_subdirectory(iDyn)
add_subdirectory(ctrlLib)
add_subdirectory(learningMachines)

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

IF(ICUB_USE_OpenCV)
    MESSAGE(STATUS "Testing iCubVis dependent code")

    ADD_EXECUTABLE(test_icubVis smoke-tests/icubVis.cpp)
    TARGET_LINK_LIBRARIES(test_icubVis ${YARP_LIBRARIES} iCubVis)

    ### execute tests
    GET_TARGET_PROPERTY(EXELOC test_icubVis LOCATION_RELEASE)
    ADD_TEST(test_icubVis ${EXELOC})
ELSE()
    MESSAGE(STATUS "OpenCV not found")
ENDIF()

IF(ICUB_USE_IPOPT)
    MESSAGE(STATUS "Testing IPOPT dependent code")

    ADD_EXECUTABLE(test_ipopt smoke-tests/ipopt.cpp)
    TARGET_LINK_LIBRARIES(test_ipopt ${YARP_LIBRARIES} iKin)

    ### execute tests
    GET_TARGET_PROPERTY(EXELOC test_ipopt LOCATION_RELEASE)
    ADD_TEST(test_ipopt ${EXELOC})
    
    add_subdirectory(iKin)
    add_subdirectory(optimization)
ELSE()
    MESSAGE(STATUS "IPOPT not found")
ENDIF()

###################### end of test specific code

