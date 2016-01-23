

set(SOURCE_FILES renderer.cpp)
add_library(carrot ${SOURCE_FILES})
set_property(TARGET carrot PROPERTY CXX_STANDARD 14)
target_include_directories(carrot PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>)