CPMAddPackage(
    NAME mongocxx
    VERSION r3.7.0
    URL https://github.com/mongodb/mongo-cxx-driver/archive/refs/tags/r3.7.0-beta1.zip
    OPTIONS
    "ENABLE_TESTS OFF"
    "BUILD_VERSION r3.7.0"
    "CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/build/garbage/mongo-cxx-driver"
)
