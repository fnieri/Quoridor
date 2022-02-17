cmake_minimum_required(VERSION 3.2)

project(Quoridor
        VERSION 0.1
        LANGUAGES CXX
        )

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")

add_executable(quoridor
        src/main.cpp
        )

target_link_libraries(quoridor ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(quoridor ${LIBBSONCXX_LIBRARIES})

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(PREFIX qrd)

# Dependencies
include(cmake/CPM.cmake)
include(cmake/AddCatch2.cmake)
include(cmake/AddSockpp.cmake)
include(cmake/AddFTXUI.cmake)

add_subdirectory(src)

#add_subdirectory(tests)