# Library of the project, can be linked to the tests
add_library(${PREFIX}_server
    PasswordEncrypter.cpp
    LandingPool.cpp
    UserHandler.cpp
    ServerUser.cpp
    GameHandler.cpp
    ChatBox.cpp
    AuthHandler.cpp
    RelationsHandler.cpp
    Database.cpp
    Config.cpp
    EloCalculator.cpp
    )

target_link_libraries(${PREFIX}_server
    PUBLIC
        nlohmann_json
        sockpp
        ${PREFIX}_common
        ${PREFIX}_client  # temporary, for GameModel
        bsoncxx_shared
        mongocxx_shared
        stdc++fs
    PRIVATE
        cryptopp_shared
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

target_compile_features(server PRIVATE
  cxx_std_17 
)
