cmake_minimum_required(VERSION 3.13)
project(curstrpo C)

set(CMAKE_C_STANDARD 99)

add_executable(curstrpo main.c functions.h notepadpw.c weather.c ipcheck.c browser.c fun.c)
target_link_libraries(curstrpo curl)