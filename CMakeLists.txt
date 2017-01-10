#  Copyright (c) 2015-2016 Christopher Hinz
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.4)
enable_testing()
project(carrot)

set(CARROT_VERSION 0.1.0)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An expressive diagnostic rendering library.")
SET(CPACK_PACKAGE_VENDOR "Christopher Hinz")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")

set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}-src")
set(CPACK_SOURCE_IGNORE_FILES "${CMAKE_CURRENT_BINARY_DIR}/;/.git/;/.kdev4/;/.idea/;~$;${CPACK_SOURCE_IGNORE_FILES}")

include(CPack)

add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

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

include(enableLTO)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
find_package(Sphinx)
  
if(DOXYGEN_FOUND)
  
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile @ONLY)

  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/latex)
      
  add_custom_target(api_doc
  ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile
  COMMAND 
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc
  COMMENT "Generating API documentation with Doxygen." VERBATIM)

  list(APPEND CARROT_DOC_TARGETS api_doc)

  if(SPHINX_FOUND)
  
if(NOT DEFINED SPHINX_THEME)
  set(SPHINX_THEME default)
endif()
if(NOT DEFINED SPHINX_THEME_DIR)
  set(SPHINX_THEME_DIR)
endif()

set(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/_build")

set(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_doctrees")

set(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/doc/html/user_guide")
set(SPHINX_LATEX_DIR "${CMAKE_CURRENT_BINARY_DIR}/doc/latex/user_guide")
configure_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/doc/user-guide/conf.py.in"
      "${BINARY_BUILD_DIR}/conf.py"
      @ONLY)

add_custom_target(user_guide
      ${SPHINX_EXECUTABLE}
      -q -b html
      -c "${BINARY_BUILD_DIR}"
      -d "${SPHINX_CACHE_DIR}"
      "${CMAKE_CURRENT_SOURCE_DIR}/doc/user-guide"
      "${SPHINX_HTML_DIR}"
      COMMENT "Building user guide with Sphinx."
      DEPENDS api_doc)

list(APPEND CARROT_DOC_TARGETS user_guide)

add_custom_target(user_guide_latex
      ${SPHINX_EXECUTABLE}
      -q -b latex
      -c "${BINARY_BUILD_DIR}"
      -d "${SPHINX_CACHE_DIR}"
      "${CMAKE_CURRENT_SOURCE_DIR}/doc/user-guide"
      "${SPHINX_LATEX_DIR}"
      COMMENT "Building user guide (latex version) with Sphinx.")

  endif(SPHINX_FOUND)

endif(DOXYGEN_FOUND)

add_custom_target(doc DEPENDS ${CARROT_DOC_TARGETS} COMMENT "Generating the documentation.")

feature_summary(WHAT ALL)
