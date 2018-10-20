#  Copyright (c) 2015-2017 Christopher Hinz
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.8)
project(carrot)

enable_testing()

set(CARROT_VERSION 0.2.0)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An expressive diagnostic rendering library.")
SET(CPACK_PACKAGE_VENDOR "Christopher Hinz")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}${CARROT_VERSION_AFFIX}")
set(CPACK_GENERATOR "7Z;TBZ2;TGZ;TXZ;ZIP")

set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-src")
set(CPACK_SOURCE_IGNORE_FILES "${CMAKE_CURRENT_BINARY_DIR}/;/.git/;/.kdev4/;/.idea/;~$;${CPACK_SOURCE_IGNORE_FILES}")
set(CPACK_SOURCE_GENERATOR "7Z;TBZ2;TGZ;TXZ;ZIP")

include(CPack)

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

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${PROJECT_SOURCE_DIR}/external/catch/cmake)

message(STATUS "The cmake module path is: ${CMAKE_MODULE_PATH}")

option(CARROT_ENABLE_SANITIZERS "Enable the address and undefined behaviour sanitizer" OFF)

if(CARROT_ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=address,undefined)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined")
endif()

option(CARROT_ANALYSE_COVERAGE "Enable code coverage analysis support." OFF)

if (CARROT_ANALYSE_COVERAGE)
    if(CMAKE_COMPILER_IS_GNUCXX)
        include(CodeCoverage)
        add_custom_target(ctest COMMAND ${CMAKE_CTEST_COMMAND})
        setup_target_for_coverage(coverage ctest coverage)
        add_compile_options(--coverage)
        link_libraries(--coverage)
    else()
        message(WARNING "Code coverage analysis is only supported with GCC.")
    endif()
endif()

find_program(CARROT_CLANG_TIDY clang-tidy)

if (CARROT_CLANG_TIDY)
    set(CARROT_HAS_CLANG_TIDY TRUE)
else()
    set(CARROT_HAS_CLANG_TIDY FALSE)
endif()

option(CARROT_RUN_CLANG_TIDY "Toggle if CMake should run clang-tidy during compilation." ${CARROT_HAS_CLANG_TIDY})

if (CARROT_RUN_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy;-p;${CMAKE_BINARY_DIR})
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
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
