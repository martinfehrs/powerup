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

include(CTest)
enable_testing()

add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE ${PROJECT_SOURCE_DIR}/third_party/catch2)

if(BUILD_TESTING)

    add_executable(legacy_iterator_test test/legacy_iterator.cpp)
    target_link_libraries(legacy_iterator_test powerup catch2)

    add_executable(cpp17_backports_test test/cpp17_backports.cpp)
    target_link_libraries(cpp17_backports_test powerup catch2)

else(BUILD_TESTING)

    add_executable(legacy_iterator_test EXCLUDE_FROM_ALL test/legacy_iterator.cpp)
    target_link_libraries(legacy_iterator_test powerup)

    add_executable(cpp17_backports_test EXCLUDE_FROM_ALL test/cpp17_backports.cpp)
    target_link_libraries(cpp17_backports_test powerup)

endif(BUILD_TESTING)

add_test(NAME is_same_v     COMMAND cpp17_backports_test [is_same_v]    )
add_test(NAME void_t        COMMAND cpp17_backports_test [void_t]       )
add_test(NAME bool_constant COMMAND cpp17_backports_test [bool_constant])
add_test(NAME conjunction   COMMAND cpp17_backports_test [conjunction]  )
add_test(NAME is_swappable  COMMAND cpp17_backports_test [is_swappable] )

#add_test(legacy_iterator_test_build
#  "${CMAKE_COMMAND}"
#    --build "${CMAKE_BINARY_DIR}"
#    --config "$<CONFIG>"
#    --target legacy_iterator_test
#)

#add_test(cpp17_backports_test_build
#  "${CMAKE_COMMAND}"
#    --build "${CMAKE_BINARY_DIR}"
#    --config "$<CONFIG>"
#    --target cpp17_backports_test
#)

#add_custom_target(check
#    COMMAND ${CMAKE_CTEST_COMMAND}
#      --force-new-ctest-process --output-on-failure
#      --build-config "$<CONFIG>"
#)


