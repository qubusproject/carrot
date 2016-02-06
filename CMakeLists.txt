cmake_minimum_required(VERSION 3.4)
enable_testing()
project(carrot)

set(CARROT_VERSION 0.1.0)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

if(POLICY CMP0053)
    cmake_policy(SET CMP0053 NEW)
endif()

if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE Release CACHE STRING
            "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel."
            FORCE)
endif()

message(STATUS "The install prefix is: ${CMAKE_INSTALL_PREFIX}")

set(CARROT_CMAKE_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/lib/cmake/carrot)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

message(STATUS "The cmake module path is: ${CMAKE_MODULE_PATH}")

option(CARROT_ENABLE_ADDRESS_SANITIZER "Enable the address sanitizer" OFF)

if(CARROT_ENABLE_ADDRESS_SANITIZER)
    add_compile_options(-fsanitize=address)
endif()

include(GenerateExportHeader)
include(FeatureSummary)

add_subdirectory(src)
add_subdirectory(tests)

feature_summary(WHAT ALL)