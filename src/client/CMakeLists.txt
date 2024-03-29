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
        MainModel.cpp
        MainController.cpp
        TerminalVue.cpp
        ServerBridge.cpp
        ServerController.cpp
        GameModel.cpp
        QtVue.cpp
        QtVue.ui
        ../server/Config.cpp
        )


find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

target_link_libraries(${PREFIX}_client
        PUBLIC nlohmann_json ftxui::screen ftxui::dom ftxui::component sockpp pthread Qt5::Core Qt5::Gui Qt5::Widgets ${PREFIX}_common
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
