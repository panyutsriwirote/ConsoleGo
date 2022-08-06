cmake_minimum_required(VERSION 3.23.1)
project(Go)
include_directories(./include)
add_executable(go main.c board.c play.c)