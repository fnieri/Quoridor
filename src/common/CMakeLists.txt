# Library of the project, can be linked to the tests
add_library(${PREFIX}_common

  SerializableMessageFactory.cpp
    Stringable.cpp
    Point.cpp
    SocketUser.cpp
    Observer.cpp
    RequestHandler.cpp
    JoinGame.cpp
)

target_include_directories(${PREFIX}_common
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PREFIX}_common

PUBLIC
    nlohmann_json
PRIVATE
    sockpp

)
