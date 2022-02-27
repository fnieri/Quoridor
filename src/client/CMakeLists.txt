# Library of the project, can be linked to the tests
add_library(${PREFIX}_client
        Board.cpp
        BoardComponent.cpp
        Cell.cpp
        Corridor.cpp
        Point.cpp
        Stringable.cpp
        Player.cpp
        PlayerAction.cpp
        WallAction.cpp
        WallEnum.h
        PlayerAction.h
        TerminalVue.cpp
        GameController.cpp
        )

target_link_libraries(${PREFIX}_client
        PUBLIC nlohmann_json ftxui::screen ftxui::dom ftxui::component
)

target_include_directories(${PREFIX}_client
        PUBLIC
        ${CMAKE_SOURCE_DIR}
        )

add_executable(client
        main.cpp
        )

# Link the project libraries to the executable
target_link_libraries(client
        PRIVATE
        ${PREFIX}_client
        )