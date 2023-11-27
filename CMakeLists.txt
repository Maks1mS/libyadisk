cmake_minimum_required(VERSION 3.5)
project(YaDisk)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
find_package(Neon REQUIRED)
find_package(JsonC REQUIRED)

add_library(yadisk src/yandex_disk_api.c)
add_executable(test-app tests/app.c)

target_include_directories(yadisk PRIVATE ${NEON_INCLUDE_DIR} ${JSON_C_INCLUDE_DIR})
target_link_libraries(yadisk ${NEON_LIBRARIES} ${JSON_C_LIBRARIES})

target_include_directories(test-app PRIVATE "${CMAKE_SOURCE_DIR}/src" ${NEON_INCLUDE_DIR} ${JSON_C_INCLUDE_DIR})
target_link_libraries(test-app yadisk)