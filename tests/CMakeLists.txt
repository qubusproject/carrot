#  Copyright (c) 2015-2017 Christopher Hinz
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

option(CARROT_BUILD_TESTS "build the carrot test suite" OFF)

if (CARROT_BUILD_TESTS)

enable_testing()

find_package(GTest REQUIRED)

add_executable(color color.cpp)
target_link_libraries(color PRIVATE carrot GTest::GTest GTest::Main)
gtest_add_tests(TARGET color)

add_executable(default_style default_style.cpp)
target_link_libraries(default_style PRIVATE carrot GTest::GTest GTest::Main)
gtest_add_tests(TARGET default_style)

endif()