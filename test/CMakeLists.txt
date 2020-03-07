list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib")
include(Catch)

if(BUILD_TESTING)

    add_executable(type_traits_test type_traits.cpp)
    target_link_libraries(type_traits_test powerup Catch2::Catch2)

    add_executable(legacy_iterator_test legacy_iterator.cpp)
    target_link_libraries(legacy_iterator_test powerup Catch2::Catch2)

else(BUILD_TESTING)

    add_executable(type_traits_test EXCLUDE_FROM_ALL type_traits.cpp)
    target_link_libraries(type_traits_test powerup Catch2::Catch2)

    add_executable(legacy_iterator_test EXCLUDE_FROM_ALL legacy_iterator.cpp)
    target_link_libraries(legacy_iterator_test powerup Catch2::Catch2)

endif(BUILD_TESTING)

catch_discover_tests(type_traits_test)
catch_discover_tests(legacy_iterator_test)

