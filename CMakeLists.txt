cmake_minimum_required(VERSION 3.25)
project(MySort C)

set(CMAKE_C_STANDARD 11)

add_executable(MySort MySort.c shell.c heap.c merge.c quick.c)