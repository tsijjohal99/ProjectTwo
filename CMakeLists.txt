cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ProjectTwo VERSION 1.0)

add_subdirectory(include)
add_subdirectory(src)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
