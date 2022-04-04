cmake_minimum_required(VERSION 3.21)
project(Clientee)

set(CMAKE_CXX_STANDARD 14)

add_executable(Clientee Cliente.c Socket_Cliente.c Socket_Cliente.h Socket.h Socket.c)
