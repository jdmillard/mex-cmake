cmake_minimum_required(VERSION 3.0)
project(mex-cmake)

# use c++ 11
set(CMAKE_CXX_STANDARD 11)

# make local header files available
include_directories(include)

# queue up the source files for compilation
add_executable(mex-cmake
               src/main.cpp
               src/my_class.cpp)
