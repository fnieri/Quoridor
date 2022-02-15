# Library of the project, can be linked to the tests
add_library(${PREFIX}_common
    Stringable.cpp
    Point.cpp
    SocketUser.cpp
    Observer.cpp
)

target_include_directories(${PREFIX}_common
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PREFIX}_common
    PRIVATE
        sockpp
)

# # Link the project libraries to the executable
# target_link_libraries(quoridor-client
#     PRIVATE
#         src
# )
