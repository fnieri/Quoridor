include(CTest)
find_package(Catch2 REQUIRED)
enable_testing()
add_executable(quoridor_tests main.cpp)
add_test(quoridor_tests Test_PasswordEncrypter.cpp)

target_link_libraries(quoridor_tests PRIVATE Catch2::Catch2WithMain src)
