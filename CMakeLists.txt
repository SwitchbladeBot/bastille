cmake_minimum_required(VERSION 3.16)
project(Bastille)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-DV8_COMPRESS_POINTERS -Wno-unused-variable")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

set(V8_COMPRESS_POINTER TRUE)
set(V8_31BIT_SMIS_ON_64BIT_ARCH TRUE)

find_package(Threads REQUIRED)

file(GLOB_RECURSE Bastille_SRC
        "src/*.h"
        "src/*.cpp"
        )

add_executable(Bastille src/main.cpp ${Bastille_SRC})

target_precompile_headers(Bastille PRIVATE ${CMAKE_SOURCE_DIR}/src/pch.h)

target_link_libraries(Bastille PRIVATE Threads::Threads)
target_link_libraries(Bastille PRIVATE ${CMAKE_SOURCE_DIR}/vendor/v8/libv8.a)

# C++ Requests: Curl for People
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/cpr)
target_link_libraries(Bastille PRIVATE cpr::cpr)

# C++ Requests: Curl for People
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/served)
target_link_libraries(Bastille PRIVATE served)
target_include_directories(Bastille PUBLIC ${CMAKE_SOURCE_DIR}/vendor/served/src)

target_include_directories(Bastille PUBLIC ${CMAKE_SOURCE_DIR}/vendor/json/single_include)
target_include_directories(Bastille PUBLIC ${CMAKE_SOURCE_DIR}/vendor/v8pp)
target_include_directories(Bastille PUBLIC ${CMAKE_SOURCE_DIR}/vendor/v8/include)