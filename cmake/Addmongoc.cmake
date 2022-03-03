CPMAddPackage(
    NAME mongoc
    VERSION 1.21.1
    URL https://github.com/mongodb/mongo-c-driver/archive/refs/tags/1.21.1.zip
    OPTIONS
    "ENABLE_AUTOMATIC_INIT_AND_CLEANUP OFF"
    "ENABLE_BSON ON"
    "ENABLE_TESTS OFF"
    "ENABLE_EXAMPLES OFF"
    "ENABLE_UNINSTALL OFF"
)
