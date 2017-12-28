#  Copyright (c) 2015-2017 Christopher Hinz
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

option(CARROT_BUILD_TESTS "build the carrot test suite" OFF)

if (CARROT_BUILD_TESTS)

find_package(GTest REQUIRED)

add_executable(color color.cpp)
target_link_libraries(color PRIVATE carrot GTest::GTest GTest::Main)

if (CMAKE_VERSION VERSION_LESS 3.10)
    gtest_add_tests(TARGET color)
else()
    gtest_discover_tests(color)
endif()

add_executable(default_style default_style.cpp)
target_link_libraries(default_style PRIVATE carrot GTest::GTest GTest::Main)

if (CMAKE_VERSION VERSION_LESS 3.10)
    gtest_add_tests(TARGET default_style)
else()
    gtest_discover_tests(default_style)
endif()

add_executable(rendering rendering.cpp)
target_link_libraries(rendering PRIVATE carrot GTest::GTest GTest::Main)

if (CMAKE_VERSION VERSION_LESS 3.10)
    gtest_add_tests(TARGET rendering)
else()
    gtest_discover_tests(rendering)
endif()

endif()