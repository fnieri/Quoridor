cmake_minimum_required(VERSION 3.2)

project(Quoridor
        VERSION 0.1
        LANGUAGES CXX  # CPP
        )

option(BUILD_SHARED_LIBS "Build libraries as shared as opposed to static" ON)

enable_testing()

set(CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(PREFIX qrd)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

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
