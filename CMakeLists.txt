cmake_minimum_required(VERSION 3.20)

project(heavy_hitters LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(misra-gries
    src/misra-gries.cpp
    src/sketch.cpp
)

target_include_directories(misra-gries PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
