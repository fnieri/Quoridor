# Library of the project, can be linked to the tests
add_library(quoridor_server
    PasswordEncrypter.cpp   
)

target_link_libraries(quoridor_server
    PRIVATE
        cryptopp
)

target_include_directories(quoridor_server
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

add_executable(server.out
    main.cpp
)

# Link the project libraries to the executable
target_link_libraries(server.out
    PRIVATE
        quoridor_server
)
