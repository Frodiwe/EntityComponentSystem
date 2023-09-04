cmake_minimum_required(VERSION 3.27)
project(cpp_template)

set(CMAKE_CXX_STANDARD 17)
set(MONGOCXX_INCLUDE_DIR /usr/local/include)

add_executable(cpp_template main.cpp)

target_link_libraries(cpp_template PUBLIC)