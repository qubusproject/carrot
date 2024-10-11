#  Copyright (c) 2015-2017 Christopher Hinz
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

option(CARROT_BUILD_TESTS "build the carrot test suite" OFF)

if (CARROT_BUILD_TESTS)

find_package(Catch2 3 CONFIG REQUIRED)

include(Catch)

add_executable(color color.cpp)
target_link_libraries(color PRIVATE carrot Catch2::Catch2WithMain)

catch_discover_tests(color)

add_executable(default_style default_style.cpp)
target_link_libraries(default_style PRIVATE carrot Catch2::Catch2WithMain)

catch_discover_tests(default_style)

add_executable(rendering rendering.cpp)
target_link_libraries(rendering PRIVATE carrot Catch2::Catch2WithMain)

catch_discover_tests(rendering)

endif()