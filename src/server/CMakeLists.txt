# Library of the project, can be linked to the tests
add_library(${PREFIX}_server
    PasswordEncrypter.cpp
    LandingPool.cpp
    UserHandler.cpp
    ServerUser.cpp
    GameHandler.cpp
    ChatBox.cpp
    # AuthHandler.cpp
    Database.cpp
    SerializableMessageFactory.cpp
    )

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")

target_link_libraries(${PREFIX}_server
    PUBLIC
        nlohmann_json
        sockpp
        ${PREFIX}_common
    PRIVATE
        cryptopp-shared
        pthread
        mongo::bsoncxx_shared
        mongo::mongocxx_shared
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

target_compile_features(server PRIVATE cxx_std_17)
