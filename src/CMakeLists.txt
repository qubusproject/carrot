option(BUILD_SHARED_LIBS "Build the library as a shared library." OFF)

find_package(Boost 1.58.0 REQUIRED)

find_package(Curses)

set(INCLUDE_FILES irregular_grid_block.hpp form.hpp frame_block.hpp form_view.hpp text_block.hpp grid_block.hpp
        underline_block.hpp caret_underline_block.hpp block.hpp carrot.hpp empty_block.hpp target_info.hpp
        style_flags.hpp glyph.hpp indent_block.hpp line_block.hpp list_block.hpp progress_bar_block.hpp checkbox_list_block.hpp)

foreach(file IN LISTS INCLUDE_FILES)
    list(APPEND FULL_INCLUDE_FILES ${CMAKE_SOURCE_DIR}/include/carrot/${file})
endforeach()

set(SOURCE_FILES irregular_grid_block.cpp form.cpp frame_block.cpp form_view.cpp text_block.cpp grid_block.cpp
        underline_block.cpp caret_underline_block.cpp empty_block.cpp target_info.cpp style_flags.cpp glyph.cpp indent_block.cpp line_block.cpp
        list_block.cpp progress_bar_block.cpp checkbox_list_block.cpp block.cpp)
add_library(carrot ${SOURCE_FILES} ${FULL_INCLUDE_FILES})
target_compile_features(carrot PUBLIC cxx_final cxx_override cxx_auto_type cxx_range_for
        cxx_generic_lambdas cxx_return_type_deduction)
target_include_directories(carrot PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> ${Boost_INCLUDE_DIRS})
target_link_libraries(carrot PUBLIC ${Boost_LIBRARIES})

if (CURSES_FOUND)
    target_include_directories(carrot PUBLIC ${CURSES_INCLUDE_DIR})
    target_link_libraries(carrot PUBLIC ${CURSES_LIBRARIES})
    target_compile_definitions(carrot PRIVATE -DHAVE_TERMINFO)
endif()

generate_export_header(carrot)

set_property(TARGET carrot PROPERTY VERSION 0.1.0)
set_property(TARGET carrot PROPERTY SOVERSION 0)
set_property(TARGET carrot PROPERTY INTERFACE_carrot_MAJOR_VERSION 0)
set_property(TARGET carrot PROPERTY INTERFACE_carrot_MINOR_VERSION 1)
set_property(TARGET carrot APPEND PROPERTY COMPATIBLE_INTERFACE_STRING carrot_MAJOR_VERSION)
set_property(TARGET carrot APPEND PROPERTY COMPATIBLE_INTERFACE_STRING carrot_MINOR_VERSION)

install(DIRECTORY ../include DESTINATION .
        FILES_MATCHING PATTERN "*.hpp")

install(TARGETS carrot EXPORT carrot-targets
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/carrot/carrot-config-version.cmake"
        VERSION 0.1.0
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT carrot-targets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/carrot/carrot-targets.cmake"
        NAMESPACE carrot::
        )

configure_file(../cmake/carrot-config.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/carrot/carrot-config.cmake"
        COPYONLY
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

install(FILES
        ../cmake/carrot-config.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/carrot/carrot-config-version.cmake"
        DESTINATION
        ${ConfigPackageLocation})