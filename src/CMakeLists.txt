#  Copyright (c) 2015-2020 Christopher Hinz
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

option(BUILD_SHARED_LIBS "Build the library as a shared library." OFF)

option(CARROT_WITH_UNICODE_SUPPORT "Enable support for Unicode." OFF)

option(CARROT_WITH_EXPERIMENTAL_FEATURES "Enable experimental features." OFF)
mark_as_advanced(CARROT_WITH_EXPERIMENTAL_FEATURES)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

find_package(Boost 1.58.0 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

find_package(Curses CONFIG)

add_library(carrot)

target_compile_features(carrot PUBLIC cxx_std_17)
target_include_directories(carrot PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interface> $<INSTALL_INTERFACE:include>)
target_link_libraries(carrot PUBLIC Boost::Boost PRIVATE fmt::fmt)
target_compile_options(carrot PRIVATE ${LTO_CXX_OPTIONS})
target_link_libraries(carrot PRIVATE "${LTO_CXX_OPTIONS}")
set_target_properties(carrot PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(interface/carrot)

target_sources(carrot PRIVATE irregular_grid_block.cpp
                              plain_form.cpp
                              frame_block.cpp
                              form_view.cpp
                              text_block.cpp
                              grid_block.cpp
                              underline_block.cpp
                              caret_underline_block.cpp
                              empty_block.cpp
                              target_info.cpp
                              glyph.cpp
                              indent_block.cpp
                              line_block.cpp
                              list_block.cpp
                              progress_bar_block.cpp
                              checkbox_list_block.cpp
                              block.cpp
                              caret_block.cpp
                              style.cpp
                              color.cpp
                              color_map.cpp
                              placeholder_block.cpp
                              table_block.cpp)

if (CARROT_WITH_EXPERIMENTAL_FEATURES)
    CHECK_CXX_COMPILER_FLAG(-fconcepts COMPILER_HAS_GCC_CONCEPT_FLAG)

    if (COMPILER_HAS_GCC_CONCEPT_FLAG AND NOT CARROT_HAS_CLANG_TIDY)
        target_compile_options(carrot PUBLIC -fconcepts)
    endif()
endif()

generate_export_header(carrot EXPORT_FILE_NAME carrot_export.hpp)
target_include_directories(carrot PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
set_target_properties(carrot PROPERTIES CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN 1)

if (CURSES_FOUND)
    target_include_directories(carrot PRIVATE ${CURSES_INCLUDE_DIR})
    target_link_libraries(carrot PRIVATE ${CURSES_LIBRARIES})
    target_compile_definitions(carrot PRIVATE -DHAVE_TERMINFO)
endif()

if (CARROT_WITH_UNICODE_SUPPORT)
    find_package(ICU CONFIG COMPONENTS uc data REQUIRED)

    target_sources(carrot PRIVATE grapheme_cluster_view.hpp grapheme_cluster_view.cpp)
    target_link_libraries(carrot PRIVATE ICU::uc ICU::data)
    target_compile_definitions(carrot PRIVATE -DCARROT_WITH_UNICODE_SUPPORT)
endif()

target_compile_options(carrot PUBLIC $<$<CXX_COMPILER_ID:MSVC>:-EHsc>)

set_property(TARGET carrot PROPERTY VERSION 0.2.0)
set_property(TARGET carrot PROPERTY SOVERSION 0)
set_property(TARGET carrot PROPERTY INTERFACE_carrot_MAJOR_VERSION 0)
set_property(TARGET carrot PROPERTY INTERFACE_carrot_MINOR_VERSION 2)
set_property(TARGET carrot APPEND PROPERTY COMPATIBLE_INTERFACE_STRING carrot_MAJOR_VERSION)
set_property(TARGET carrot APPEND PROPERTY COMPATIBLE_INTERFACE_STRING carrot_MINOR_VERSION)

install(DIRECTORY interface/carrot DESTINATION ./include/carrot
        FILES_MATCHING PATTERN "*.hpp")

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/carrot_export.hpp DESTINATION ./include)

install(TARGETS carrot EXPORT carrot-targets
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/carrot/carrot-config-version.cmake"
        VERSION 0.2.0
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT carrot-targets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/carrot/carrot-targets.cmake"
        NAMESPACE carrot::
        )

set(ConfigPackageLocation lib/cmake/carrot)

install(EXPORT carrot-targets
        FILE
        carrot-targets.cmake
        NAMESPACE
        carrot::
        DESTINATION
        ${ConfigPackageLocation}
        )

configure_package_config_file(
        ../cmake/carrot-config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/carrot-config.cmake
        INSTALL_DESTINATION ${ConfigPackageLocation}
        )

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/carrot-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/carrot/carrot-config-version.cmake"
        DESTINATION
        ${ConfigPackageLocation})