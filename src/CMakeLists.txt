find_package(Boost 1.58.0 REQUIRED)

set(SOURCE_FILES renderer.cpp)
add_library(carrot ${SOURCE_FILES})
set_property(TARGET carrot PROPERTY CXX_STANDARD 14)
set_property(TARGET carrot PROPERTY CXX_STANDARD_REQUIRED On)
target_include_directories(carrot PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> ${Boost_INCLUDE_DIRS})
target_link_libraries(carrot PUBLIC ${Boost_LIBRARIES})

generate_export_header(carrot)

set_property(TARGET carrot PROPERTY VERSION 0.1.0)
set_property(TARGET carrot PROPERTY SOVERSION 0)
set_property(TARGET carrot PROPERTY INTERFACE_carrot_MAJOR_VERSION 0)
set_property(TARGET carrot PROPERTY INTERFACE_carrot_MINOR_VERSION 1)
set_property(TARGET carrot APPEND PROPERTY COMPATIBLE_INTERFACE_STRING carrot_MAJOR_VERSION)
set_property(TARGET carrot APPEND PROPERTY COMPATIBLE_INTERFACE_STRING carrot_MINOR_VERSION)

install(DIRECTORY ../carrot/ DESTINATION include/carrot
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

install(
        FILES
        ../cmake/carrot-config.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/carrot/carrot-config-version.cmake"
        DESTINATION
        ${ConfigPackageLocation})