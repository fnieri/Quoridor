##Library of the project, can be linked to the tests
#add_library(src
#        ../server/PasswordEncrypter.cpp
#        # Point.cpp
#        )
#
#target_link_libraries(src
#        PRIVATE
#        cryptopp-shared
#        )
#
#add_executable(quoridor-client
#        ../client/main.cpp
#        )
#
## Link the project libraries to the executable
#target_link_libraries(quoridor-client
#        PRIVATE
#        src
#        PRIVATE ftxui::screen
#        PRIVATE ftxui::dom
#        PRIVATE ftxui::component # Not needed for this example.
#        )
#
#include_directories(../server)
#include_directories(../client)
#include_directories(../common)
