find_package(Catch2 REQUIRED)

set(quoridor_test_suites
    # quoridor_client_tests
    # quoridor_server_tests
    quoridor_common_tests
)

# Names of the test files without the extention
set(quoridor_common_tests
    Test_PasswordEncrypter
)

foreach(test_suite IN LISTS quoridor_test_suites)
    add_executable(${test_suite} ${${test_suite}})
    add_test(NAME ${test_suite} COMMAND ${test_suite})
    target_link_libraries(${test_suite} PRIVATE Catch2::Catch2WithMain src)
endforeach()
