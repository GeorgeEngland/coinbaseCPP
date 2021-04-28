cmake_minimum_required(VERSION 3.9)
project(coin)

find_library(cpprestsdk-lib cpprest)
message(STATUS "cpprestsdk-lib = ${cpprestsdk-lib}")
set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)

find_package(cpprestsdk REQUIRED)

find_package(benchmark REQUIRED)

message(STATUS "RestSDK Lib is ${cpprestsdk_DIR}")

message(STATUS "Benchmark Lib is ${benchmark_DIR}")


add_executable(coin coinAPI.cpp ./src/jsoncpp.cpp ./src/coinBaseClient.cpp ./src/orderBook.cpp ./src/parser.cpp)
target_link_libraries(coin PRIVATE pthread cpprestsdk::cpprest sqlite3)

add_executable(testMe ./test/main.cpp ./src/jsoncpp.cpp ./src/orderBook.cpp ./src/coinBaseClient.cpp)
target_link_libraries(testMe benchmark::benchmark pthread cpprestsdk::cpprest sqlite3)