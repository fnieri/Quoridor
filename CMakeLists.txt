cmake_minimum_required(VERSION 3.2)

project(Quoridor
    VERSION 0.1
    LANGUAGES CXX  # CPP
)

enable_testing()

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tests)
