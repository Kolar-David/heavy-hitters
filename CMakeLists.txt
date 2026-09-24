cmake_minimum_required(VERSION 3.20)

project(stream_summaries LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(summary-runner
    src/main.cpp
    src/runner.cpp
    src/arguments.cpp
    src/io.cpp
    src/summary_factory.cpp

    src/summaries/misra_gries.cpp
        src/estimate.h
)

target_include_directories(summary-runner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

