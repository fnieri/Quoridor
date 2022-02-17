add_library(${PREFIX}_common
    JoinGame.cpp
)

target_include_directories(${PREFIX}_common
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PREFIX}_common
    PRIVATE
        sockpp
)