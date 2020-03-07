list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib")
include(Catch)

if(BUILD_TESTING)

    add_executable(cpp17_backports_test cpp17_backports.cpp)
    target_link_libraries(cpp17_backports_test powerup Catch2::Catch2)

    add_executable(legacy_iterator_test legacy_iterator.cpp)
    target_link_libraries(legacy_iterator_test powerup Catch2::Catch2)

else(BUILD_TESTING)

    add_executable(cpp17_backports_test EXCLUDE_FROM_ALL cpp17_backports.cpp)
    target_link_libraries(cpp17_backports_test powerup Catch2::Catch2)

    add_executable(legacy_iterator_test EXCLUDE_FROM_ALL legacy_iterator.cpp)
    target_link_libraries(legacy_iterator_test powerup Catch2::Catch2)

endif(BUILD_TESTING)

catch_discover_tests(cpp17_backports_test)
catch_discover_tests(legacy_iterator_test)

