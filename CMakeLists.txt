cmake_minimum_required(VERSION 3.20)
project("Old Tom's Trading Store" VERSION 0.0.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Old_Toms_Trading_Store
    src/main.cpp
    src/sell.cpp
    src/buy.cpp
)

target_include_directories(Old_Toms_Trading_Store PRIVATE inc)