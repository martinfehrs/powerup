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


add_subdirectory(third_party/Catch2)
include(CTest)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/third_party/Catch2/contrib")
include(Catch)
enable_testing()

if(BUILD_TESTING)

    add_executable(legacy_iterator_test test/legacy_iterator.cpp)
    target_link_libraries(legacy_iterator_test powerup Catch2::Catch2)

    add_executable(cpp17_backports_test test/cpp17_backports.cpp)
    target_link_libraries(cpp17_backports_test powerup Catch2::Catch2)

else(BUILD_TESTING)

    add_executable(legacy_iterator_test EXCLUDE_FROM_ALL test/legacy_iterator.cpp)
    target_link_libraries(legacy_iterator_test powerup Catch2::Catch2)

    add_executable(cpp17_backports_test EXCLUDE_FROM_ALL test/cpp17_backports.cpp)
    target_link_libraries(cpp17_backports_test powerup Catch2::Catch2)

endif(BUILD_TESTING)

catch_discover_tests(cpp17_backports_test)

