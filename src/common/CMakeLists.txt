# Library of the project, can be linked to the tests
add_library(${PREFIX}_common
JoinGame.cpp
SerializableMessageFactory.cpp
AuthSerializableMessageFactory.cpp
BoardActionsSerializableMessageFactory.cpp
ChatBoxSerializableMessageFactory.cpp
FriendActionsSerializableMessageFactory.cpp
GameRelatedActionsSerializableMessageFactory.cpp
ObjectExchangesSerializableMessageFactory.cpp
GameSetupSerializableMessageFactory.cpp
Stringable.cpp

../client/WallAction.cpp
../client/PlayerAction.cpp
        ../client/Board.cpp
        ../client/Player.cpp
        ../client/Corridor.cpp
        ../client/BoardComponent.cpp
        ../client/Cell.cpp
        GameConfiguration.cpp
Point.cpp
SocketUser.cpp
Observer.cpp
RequestHandler.cpp
JoinGame.cpp
)

target_link_libraries(${PREFIX}_common

PUBLIC
    nlohmann_json
PRIVATE
    sockpp

)

target_include_directories(${PREFIX}_common
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

add_executable(common
    main.cpp
)

target_link_libraries(common
    PRIVATE
    ${PREFIX}_common
)
