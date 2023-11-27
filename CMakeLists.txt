cmake_minimum_required(VERSION 3.5)
project(YaDisk)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
find_package(CURL REQUIRED)
find_package(JsonC REQUIRED)

add_library(yadisk
        src/yadisk_get_disk_resources.c
        src/yadisk_api_internal.c
        src/yadisk_api_internal.h
        src/yadisk_get_disk_resources.h
        src/yadisk.h
        src/yadisk_get_disk.c
        src/yadisk_get_disk.h
        src/yadisk_shared.c
        src/yadisk_shared.h
)
add_executable(test-app tests/app.c)

target_include_directories(
        yadisk PRIVATE
        ${CURL_INCLUDE_DIR}
        ${JSON_C_INCLUDE_DIR}
)
target_link_libraries(yadisk
        ${CURL_LIBRARIES}
        ${JSON_C_LIBRARIES}
)

target_include_directories(
        test-app PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
        ${NEON_INCLUDE_DIR}
        ${CURL_INCLUDE_DIR}
        ${JSON_C_INCLUDE_DIR}
)
target_link_libraries(
        test-app
        yadisk
)