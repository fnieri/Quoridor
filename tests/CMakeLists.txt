include(CTest)
find_package(Catch2 REQUIRED)
enable_testing()
add_executable(quoridor_tests main.cpp ../src/PasswordEncrypter.cpp)
add_test(quoridor_tests Test_PasswordEncrypter.cpp COMMAND outputTest)

target_link_libraries(quoridor_tests PRIVATE cryptopp-shared Catch2::Catch2WithMain src)
