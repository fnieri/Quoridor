set(test_suite ${PREFIX}_client_tests)

# Names of the test files without the extention
set(${test_suite}
    Test_Wall_Placement
    Test_Player_Moves
    Test_Main_Model_Controller
)

add_executable(${test_suite} ${${test_suite}})
add_test(NAME ${test_suite} COMMAND ${test_suite})
target_link_libraries(${test_suite}
    PRIVATE
        catch_main
        Catch2::Catch2
        ${PREFIX}_common
        ${PREFIX}_client
        sockpp
        pthread
)
