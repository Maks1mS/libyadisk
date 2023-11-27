INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(PKG_JSON_C json-c)

FIND_PATH(JSON_C_INCLUDE_DIR json.h
        PATHS
        ${PKG_JSON_C_INCLUDE_DIRS}
        /usr/include
        /usr/local/include
        PATH_SUFFIXES json-c
)

FIND_LIBRARY(JSON_C_LIBRARIES json-c
        ${PKG_JSON_C_LIBRARY_DIRS}
        /usr/lib
        /usr/local/lib
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(JsonC DEFAULT_MSG JSON_C_LIBRARIES JSON_C_INCLUDE_DIR)
