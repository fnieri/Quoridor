set(test_suite ${PREFIX}_server_tests)

# Names of the test files without the extention
set(${test_suite}
    Test_DatabaseHandler
    Test_PasswordEncrypter
    Test_LandingPool
)

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")

add_executable(${test_suite} ${${test_suite}})
add_test(NAME ${test_suite} COMMAND ${test_suite})
target_link_libraries(${test_suite} PRIVATE catch_main Catch2::Catch2 ${PREFIX}_server sockpp mongo::bsoncxx_shared mongo::mongocxx_shared)

