cmake_minimum_required(VERSION 3.16)
project(Bastille)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bastille main.cpp)

target_link_libraries(Bastille STATIC ${CMAKE_SOURCE_DIR}/vendor/v8/libv8.a)
target_include_directories(Bastille PUBLIC ${CMAKE_SOURCE_DIR}/vendor/v8/include)