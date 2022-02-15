cmake_minimum_required(VERSION 3.11)

# Library of the project, can be linked to the tests

add_executable(client
        main.cpp
        #        TerminalVue.h
        )

#add_executable(client src/main.cpp)

add_library(${PREFIX}_client
        Point.cpp
        Stringable.cpp
        TerminalVue.cpp
        )

target_link_libraries(${PREFIX}_client
        PUBLIC ftxui::screen ftxui::dom ftxui::component
        )

target_include_directories(${PREFIX}_client
        PUBLIC
        ${CMAKE_SOURCE_DIR}
        )

target_link_libraries(client
        PRIVATE ${PREFIX}_client
        )

# Link the project libraries to the executable
#target_link_libraries(client
#        PRIVATE quoridor_client
#
#        )

#install(TARGETS client RUNTIME DESTINATION "bin")

target_link_libraries(client
        PRIVATE
        ${PREFIX}_client
        )
