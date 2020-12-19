cmake_minimum_required (VERSION 3.5)
add_definitions(-Wno-sign-compare -Wno-enum-compare)

project(metric VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 11)
include_directories("${CMAKE_SOURCE_DIR}")

set(Casablanca_LIBRARIES "-lboost_system -lcrypto -lssl -lcpprest")

set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)

find_package(cpprestsdk REQUIRED NAMES cpprestsdk cpprest)

add_executable(metric main.cpp handler.cpp)

target_link_libraries(metric ${Casablanca_LIBRARIES})
