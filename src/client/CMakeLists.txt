# Library of the project, can be linked to the tests
add_library(${PREFIX}_client
        Board.cpp
        BoardComponent.cpp
        Cell.cpp
        Corridor.cpp
        Player.cpp
        PlayerAction.cpp
        WallAction.cpp
        WallEnum.h
        PlayerAction.h
        ServerBridge.cpp
        MainController.cpp
        MainModel.cpp
#        GameController.cpp
        TerminalVue.cpp
        ServerBridge.cpp
        ServerController.cpp
        )

target_link_libraries(${PREFIX}_client
        PUBLIC nlohmann_json ftxui::screen ftxui::dom ftxui::component sockpp pthread ${PREFIX}_common
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
target_compile_features(client PRIVATE cxx_std_17)
