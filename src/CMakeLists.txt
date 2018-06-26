cmake_minimum_required(VERSION 3.5)

set(PROJECTNAME icub-tutorials)

project(${PROJECTNAME})

find_package(YARP REQUIRED COMPONENTS OS sig dev math gsl)
find_package(ICUB REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ICUB_MODULE_PATH})
include(iCubOptions)

include_directories(${ICUB_INCLUDE_DIRS})

## this is for testing only, please ignore if you are reading tutorials	
include(CTest)
### end test specific code

# go by subdirectories
add_subdirectory(imageProcessing)
add_subdirectory(motorControlBasic)
add_subdirectory(motorControlAdvanced)
add_subdirectory(periodicThread)
add_subdirectory(ctrlLib)
add_subdirectory(iDyn)
add_subdirectory(rpcIdl)

if(TARGET learningMachine)
  add_subdirectory(learningMachines)
else()
  message(STATUS "Unmet dependencies, skipping learningMachines")
endif()

if(TARGET perceptiveModels)
  add_subdirectory(perceptiveModels)
else()
  message(STATUS "Unmet dependencies, skipping perceptiveModels")
endif()

if(TARGET actionPrimitives)
  add_subdirectory(actionPrimitives)
else()
  message(STATUS "Unmet dependencies, skipping actionPrimitives")
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

