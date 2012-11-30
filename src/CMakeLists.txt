CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(PROJECTNAME tutorials)

PROJECT(${PROJECTNAME})

FIND_PACKAGE(YARP)
FIND_PACKAGE(ICUB)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${YARP_MODULE_PATH})
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ICUB_MODULE_PATH})
INCLUDE(iCubHelpers)

INCLUDE_DIRECTORIES(${ICUB_INCLUDE_DIRS}
                    ${YARP_INCLUDE_DIRS})

## this is for testing only, please ignore if you are reading tutorials	
INCLUDE(CTest)
### end test specific code

# go by subdirectories
add_subdirectory(imageProcessing)
add_subdirectory(resourceFinder)
add_subdirectory(module)
add_subdirectory(motorControlBasic)
add_subdirectory(motorControlAdvanced)
add_subdirectory(rateThread)
add_subdirectory(iDyn)
add_subdirectory(ctrlLib)

## again this is for testing only, please ignore if you are reading tutorials
ADD_EXECUTABLE(test_icubVis smoke-tests/icubVis.cpp)
TARGET_LINK_LIBRARIES(test_icubVis ${YARP_LIBRARIES} iCubVis)

### execute tests
GET_TARGET_PROPERTY(EXELOC test_icubVis LOCATION_RELEASE)
ADD_TEST(test_icubVis ${EXELOC})

IF(ICUB_USE_IPOPT)
    message(STATUS "Testing IPOPT dependent code")

    ADD_EXECUTABLE(test_ipopt smoke-tests/ipopt.cpp)
    TARGET_LINK_LIBRARIES(test_ipopt ${YARP_LIBRARIES} iKin)

    GET_TARGET_PROPERTY(EXELOC test_ipopt LOCATION_RELEASE)
    ADD_TEST(test_ipopt ${EXELOC})
    
    add_subdirectory(iKin)
    add_subdirectory(optimization)
ENDIF()

###################### end of test specific code

