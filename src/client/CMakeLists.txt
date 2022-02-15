cmake_minimum_required(VERSION 3.11)

## --- Fetch FTXUI --------------------------------------------------------------
#include(FetchContent)
#
#set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
#FetchContent_Declare(ftxui
#        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
#        # Specify a GIT_TAG here.
#        )
#
#FetchContent_GetProperties(ftxui)
#if (NOT ftxui_POPULATED)
#    FetchContent_Populate(ftxui)
#    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
#endif ()
#
## ------------------------------------------------------------------------------

project(quo
        LANGUAGES CXX
        VERSION 1.0.0
        )

add_library(quoridor_tui
        TerminalVue.h
        )

target_link_libraries(quoridor_tui
        PRIVATE ftxui::screen ftxui::dom ftxui::component
        )
target_include_directories(quoridor_tui PRIVATE .)

# Library of the project, can be linked to the tests
add_library(quoridor_client
        Point.cpp
        Stringable.cpp
        #        TerminalVue.h
        )

add_executable(client
        main.cpp
        #        TerminalVue.h
        )

target_link_libraries(quoridor_client
        PUBLIC quoridor_tui
        )
#add_executable(client src/main.cpp)

target_include_directories(quoridor_client
        PUBLIC ${CMAKE_SOURCE_DIR}
        )

target_link_libraries(client
        PRIVATE quoridor_client
        )

# Link the project libraries to the executable
#target_link_libraries(client
#        PRIVATE quoridor_client
#
#        )

#install(TARGETS client RUNTIME DESTINATION "bin")

