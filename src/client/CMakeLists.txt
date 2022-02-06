# Library of the project, can be linked to the tests
# add_library(quoridor_client
#     # Point.cpp
# )

# target_include_directories(quoridor_client
#     PUBLIC
#     ${CMAKE_SOURCE_DIR}
# )

add_executable(client
    main.cpp
)

# Link the project libraries to the executable
# target_link_libraries(client
#     PRIVATE
#         quoridor_client
# )
