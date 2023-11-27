cmake_minimum_required(VERSION 3.5)
project(YaDisk)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
find_package(Neon REQUIRED)
find_package(JsonC REQUIRED)

add_library(yadisk src/yandex_disk_api.c
        tests/ctest.c)

target_include_directories(yadisk PRIVATE ${NEON_INCLUDE_DIR} ${JSON_C_INCLUDE_DIR})
target_link_libraries(yadisk ${NEON_LIBRARIES} ${JSON_C_LIBRARIES})