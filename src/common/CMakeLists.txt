# Library of the project, can be linked to the tests
add_library(${PREFIX}_common
    AuthSerializableMessageFactory.cpp
    BoardActionsSerializableMessageFactory.cpp
    ChatBoxSerializableMessageFactory.cpp
    FriendActionsSerializableMessageFactory.cpp
    GameRelatedActionsSerializableMessageFactory.cpp
    GameSetupSerializableMessageFactory.cpp
    ObjectExchangesSerializableMessageFactory.cpp
    Observer.cpp
    Point.cpp
    RequestHandler.cpp
    Serializable.cpp
    SerializableMessageFactory.cpp
    SocketUser.cpp
    Stringable.cpp
)

target_link_libraries(${PREFIX}_common
    PUBLIC
        nlohmann_json
    PRIVATE
        ${PREFIX}_client  # wtf is this doing here
        sockpp
)

target_include_directories(${PREFIX}_common
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

# add_executable(common
#     main.cpp
# )

# target_link_libraries(common
#     PRIVATE
#     ${PREFIX}_common
# )
