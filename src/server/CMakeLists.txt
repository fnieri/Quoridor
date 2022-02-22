# Library of the project, can be linked to the tests
add_library(${PREFIX}_server
    PasswordEncrypter.cpp
    AuthSerializableMessageFactory.cpp
    BoardActionsSerializableMessageFactory.cpp
    SerializableMessageFactory.cpp
    GameActionsSerializableMessageFactory.cpp
    )

target_link_libraries(${PREFIX}_server
    PUBLIC
        nlohmann_json   
        sockpp
        ${PREFIX}_common
        PRIVATE
        cryptopp-shared
        pthread
)

target_include_directories(${PREFIX}_server
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

add_executable(server
    main.cpp
)

# Link the project libraries to the executable
target_link_libraries(server
    PRIVATE
        ${PREFIX}_server
)