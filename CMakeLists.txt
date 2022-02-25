cmake_minimum_required(VERSION 3.17)
project(apathism)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fsanitize=undefined -DLOCAL -D_GLIBCXX_DEBUG")

add_executable(apathism main.cpp)