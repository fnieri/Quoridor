set(test_suite quoridor_client_tests)

# Names of the test files without the extention
set(${test_suite}
    Test_Point
)

add_executable(${test_suite} ${${test_suite}})
add_test(NAME ${test_suite} COMMAND ${test_suite})
target_link_libraries(${test_suite} PRIVATE Catch2::Catch2WithMain quoridor_client)
