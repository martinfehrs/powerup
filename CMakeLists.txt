cmake_minimum_required(VERSION 3.13)

project(powerup)

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


if (EXISTS "${CMAKE_SOURCE_DIR}/third_party/Catch2/CMakeLists.txt")
    include(CTest)
    enable_testing()
    add_subdirectory("${CMAKE_SOURCE_DIR}/third_party/Catch2")
    add_subdirectory(test)
endif()

