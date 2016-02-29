#  Copyright (c) 2016 Christopher Hinz
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(APPLE)
    # disable LTO under MacOS by default (it is not working just now)
    option(LTO_ENABLE "enable LTO support" OFF)
else()
    option(LTO_ENABLE "enable LTO support" ON)
endif()

if(${LTO_ENABLE})
    set(LTO_CXX_OPTIONS ${LTO_CXX_OPTIONS} $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Release>>:-flto -ffat-lto-objects>)
    set(LTO_C_OPTIONS ${LTO_C_OPTIONS} $<$<AND:$<C_COMPILER_ID:GNU>,$<CONFIG:Release>>:-flto -ffat-lto-objects>)
    set(LTO_Fortran_OPTIONS ${LTO_Fortran_OPTIONS} $<$<AND:$<STREQUAL:${CMAKE_Fortran_COMPILER_ID},GNU>,$<CONFIG:Release>>:-flto -ffat-lto-objects>)
endif()

if(${LTO_ENABLE})
    message(STATUS "LTO support is enabled")
else()
    message(STATUS "LTO support is disabled")
endif()