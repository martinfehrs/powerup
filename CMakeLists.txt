cmake_minimum_required(VERSION 3.13)

project(powerup)

include(FetchContent)
include(CTest)

add_library(powerup INTERFACE)

set(POWERUP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/inc)

set(POWERUP_SOURCES
    ${POWERUP_INCLUDE_DIR}/powerup/legacy_iterator.hpp
    ${POWERUP_INCLUDE_DIR}/powerup/number_ranges.hpp
    ${POWERUP_INCLUDE_DIR}/powerup/cpp17_backports.hpp
)

target_sources(powerup INTERFACE ${POWERUP_SOURCES})
target_include_directories(powerup INTERFACE ${POWERUP_INCLUDE_DIR})
target_compile_features(powerup INTERFACE cxx_std_14)

FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.11.1
)

FetchContent_GetProperties(catch2)
if(NOT catch2_POLULATED)
    FetchContent_Populate(catch2)
    add_subdirectory(${catch2_SOURCE_DIR})
endif()

enable_testing()
add_subdirectory(test)

