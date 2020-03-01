cmake_minimum_required(VERSION 3.13)

project(powerup)

add_library(powerup INTERFACE)

set(POWERUP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

set(POWERUP_SOURCES
    ${POWERUP_INCLUDE_DIR}/powerup/legacy_iterator.hpp
    ${POWERUP_INCLUDE_DIR}/powerup/number_ranges.hpp
)

target_sources(powerup INTERFACE ${POWERUP_SOURCES})
target_include_directories(powerup INTERFACE ${POWERUP_INCLUDE_DIR})
target_compile_features(powerup INTERFACE cxx_std_14)

enable_testing()

# Usable with CMake VERSION 3.17 or higher. No additional check target needed.
#list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

add_executable(legacy_iterator EXCLUDE_FROM_ALL test/legacy_iterator.cpp)
target_link_libraries(legacy_iterator powerup)

add_test(legacy_iterator_build
  "${CMAKE_COMMAND}"
    --build "${CMAKE_BINARY_DIR}"
    --config "$<CONFIG>"
    --target legacy_iterator
)

add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND}
      --force-new-ctest-process --output-on-failure
      --build-config "$<CONFIG>"
)


