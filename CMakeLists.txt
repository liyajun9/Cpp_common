cmake_minimum_required(VERSION 3.15)
project(common)

FILE(GLOB_RECURSE SRCS src/src/*)
FILE(GLOB_RECURSE HEADERS src/include/*)
add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS} src/main.cpp src/src/rdwrn.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -g -O3 -std=c++0x)
target_compile_definitions(${PROJECT_NAME} PRIVATE _LINUX_OS_ RAPIDJSON_HAS_STDSTRING USE_GMLOGAPI)

target_include_directories(${PROJECT_NAME} PRIVATE src/include)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/lib64
        ${CMAKE_CURRENT_SOURCE_DIR}/lib64/mysql
        ${CMAKE_CURRENT_SOURCE_DIR}/lib64/openssl
        ${CMAKE_CURRENT_SOURCE_DIR}/lib64/protobuf
        ${CMAKE_CURRENT_SOURCE_DIR}/lib64/rapidjson
        ${CMAKE_CURRENT_SOURCE_DIR}/lib64/zlib)

#target_link_libraries(${PROJECT_NAME} PRIVATE )
