cmake_minimum_required(VERSION 3.20)
project(371pass)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(371pass
        src/lib_cxxopts.hpp
        src/lib_json.hpp
        src/category.cpp
        src/item.cpp
        src/371pass.cpp
        src/wallet.cpp
        src/main.cpp)
