cmake_minimum_required(VERSION 3.13)

project(powerup)

add_library(powerup INTERFACE)

set(POWERUP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

set(POWERUP_SOURCES
    ${POWERUP_INCLUDE_DIR}/powerup/legacy_iterator.hpp
    ${POWERUP_INCLUDE_DIR}/powerup/number_ranges.hpp
    ${POWERUP_INCLUDE_DIR}/powerup/cpp17_backports.hpp
)

target_sources(powerup INTERFACE ${POWERUP_SOURCES})
target_include_directories(powerup INTERFACE ${POWERUP_INCLUDE_DIR})
target_compile_features(powerup INTERFACE cxx_std_14)

enable_testing()

# Usable with CMake VERSION 3.17 or higher. No additional check target needed.
#list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

add_executable(legacy_iterator_test EXCLUDE_FROM_ALL test/legacy_iterator.cpp)
target_link_libraries(legacy_iterator_test powerup)

add_executable(cpp17_backports_test EXCLUDE_FROM_ALL test/cpp17_backports.cpp)
target_link_libraries(cpp17_backports_test powerup)


add_test(legacy_iterator_test_build
  "${CMAKE_COMMAND}"
    --build "${CMAKE_BINARY_DIR}"
    --config "$<CONFIG>"
    --target legacy_iterator_test
)

add_test(cpp17_backports_test_build
  "${CMAKE_COMMAND}"
    --build "${CMAKE_BINARY_DIR}"
    --config "$<CONFIG>"
    --target cpp17_backports_test
)

add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND}
      --force-new-ctest-process --output-on-failure
      --build-config "$<CONFIG>"
)


