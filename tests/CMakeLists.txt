# Main function of Catch2
add_library(catch_main catch_main.cpp)
target_link_libraries(catch_main PRIVATE Catch2::Catch2)

add_subdirectory(server)
# add_subdirectory(client)
add_subdirectory(common)
