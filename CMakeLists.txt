cmake_minimum_required(VERSION 3.2)

project(Quoridor
    VERSION 0.1
    LANGUAGES CXX  # CPP
)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -std=c++1y  -fPIC") # -std=c++1y probably isn't mandatory
set(PREFIX qrd)

option(BUILD_SHARED_LIBS "Build libraries as shared as opposed to static" ON)

# Dependencies
include(cmake/CPM.cmake)
include(cmake/AddCatch2.cmake)
include(cmake/AddSockpp.cmake)
include(cmake/Addjson.cmake)
include(cmake/AddFTXUI.cmake)
include(cmake/Addcryptopp.cmake)
include(cmake/Addmongoc.cmake)
include(cmake/Addmongocxx.cmake)

add_subdirectory(src)
add_subdirectory(tests)
