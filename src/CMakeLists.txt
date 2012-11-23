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

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ICUB_LINK_FLAGS}")					

# Create everything needed to build our executable.
ADD_EXECUTABLE(imageProc imageProc.cpp)
ADD_EXECUTABLE(findLocation findLocation.cpp)
ADD_EXECUTABLE(lookAtLocation lookAtLocation.cpp)
ADD_EXECUTABLE(relay relay.cpp)
ADD_EXECUTABLE(tutorial_arm tutorial_arm.cpp)
ADD_EXECUTABLE(tutorial_arm_joint_impedance tutorial_arm_joint_impedance.cpp)
ADD_EXECUTABLE(tutorial_rf_basic tutorial_rf_basic.cpp)
ADD_EXECUTABLE(tutorial_rf_advanced tutorial_rf_advanced.cpp)
ADD_EXECUTABLE(tutorial_rate_thread tutorial_rate_thread.cpp)
ADD_EXECUTABLE(tutorial_module tutorial_module.cpp)
ADD_EXECUTABLE(tutorial_cartesian_interface tutorial_cartesian_interface.cpp)
ADD_EXECUTABLE(tutorial_gaze_interface tutorial_gaze_interface.cpp)

TARGET_LINK_LIBRARIES(imageProc ${YARP_LIBRARIES})
TARGET_LINK_LIBRARIES(findLocation ${YARP_LIBRARIES})
TARGET_LINK_LIBRARIES(lookAtLocation ${YARP_LIBRARIES})
TARGET_LINK_LIBRARIES(relay ${YARP_LIBRARIES})
TARGET_LINK_LIBRARIES(tutorial_arm ${YARP_LIBRARIES})
TARGET_LINK_LIBRARIES(tutorial_arm_joint_impedance ${YARP_LIBRARIES})
TARGET_LINK_LIBRARIES(tutorial_rf_basic ${YARP_LIBRARIES})
TARGET_LINK_LIBRARIES(tutorial_rf_advanced ${YARP_LIBRARIES})
TARGET_LINK_LIBRARIES(tutorial_rate_thread ${YARP_LIBRARIES})
TARGET_LINK_LIBRARIES(tutorial_module ${YARP_LIBRARIES})
TARGET_LINK_LIBRARIES(tutorial_cartesian_interface ${YARP_LIBRARIES} icubmod)
TARGET_LINK_LIBRARIES(tutorial_gaze_interface ${YARP_LIBRARIES} icubmod)

# go by subdirectories
#removing until fixed
# add_subdirectory(iDyn)

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

