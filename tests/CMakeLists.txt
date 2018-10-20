#  Copyright (c) 2015-2017 Christopher Hinz
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

option(CARROT_BUILD_TESTS "build the carrot test suite" OFF)

if (CARROT_BUILD_TESTS)

add_library(test_runner OBJECT runner.cpp)
target_include_directories(test_runner PRIVATE SYSTEM ${PROJECT_SOURCE_DIR}/external/catch/)

include(Catch)

add_executable(color color.cpp $<TARGET_OBJECTS:test_runner>)
target_include_directories(color PRIVATE SYSTEM ${PROJECT_SOURCE_DIR}/external/catch/)
target_link_libraries(color PRIVATE carrot)

catch_discover_tests(color)

add_executable(default_style default_style.cpp $<TARGET_OBJECTS:test_runner>)
target_include_directories(default_style PRIVATE SYSTEM ${PROJECT_SOURCE_DIR}/external/catch/)
target_link_libraries(default_style PRIVATE carrot)

catch_discover_tests(default_style)

add_executable(rendering rendering.cpp $<TARGET_OBJECTS:test_runner>)
target_include_directories(rendering PRIVATE SYSTEM ${PROJECT_SOURCE_DIR}/external/catch/)
target_link_libraries(rendering PRIVATE carrot)

catch_discover_tests(default_style)

endif()