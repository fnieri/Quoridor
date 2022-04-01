set(test_suite ${PREFIX}_server_tests)

# Names of the test files without the extention
set(${test_suite}
     Test_DatabaseHandler
    Test_PasswordEncrypter
    Test_LandingPool
    Test_Requests_Exchange
)

add_executable(${test_suite} ${${test_suite}})
add_test(NAME ${test_suite} COMMAND ${test_suite} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries(${test_suite} PRIVATE catch_main Catch2::Catch2 ${PREFIX}_server sockpp pthread bsoncxx_shared mongocxx_shared stdc++fs)

