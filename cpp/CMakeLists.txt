cmake_minimum_required(VERSION 3.0.0)
project(metric VERSION 0.1.0)

set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)

find_package(cpprestsdk REQUIRED NAMES cpprestsdk cpprest)

add_executable(metric main.cpp)

target_link_libraries(metric PRIVATE cpprestsdk::cpprest)
