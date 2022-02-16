# Library of the project, can be linked to the tests

add_library(${PREFIX}_server
    PasswordEncrypter.cpp
)

target_link_libraries(${PREFIX}_server
    PRIVATE
        cryptopp
)

target_include_directories(${PREFIX}_server
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

add_executable(server.out
    main.cpp
)

# Link the project libraries to the executable
target_link_libraries(server.out
    PRIVATE
        ${PREFIX}_server
)
