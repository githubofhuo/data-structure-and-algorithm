cmake_minimum_required(VERSION 3.6)
project(BigNum)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BigNum1.h)
add_executable(BigNum ${SOURCE_FILES})