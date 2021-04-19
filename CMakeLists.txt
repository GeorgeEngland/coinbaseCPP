cmake_minimum_required(VERSION 3.9)
project(coin)
set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)

find_library(cpprestsdk-lib cpprest)
message(STATUS "cpprestsdk-lib = ${cpprestsdk-lib}")
find_package(cpprestsdk REQUIRED)

find_package(benchmark REQUIRED)


message("CMAKE_CXX_FLAGS is ${CMAKE_CXX_FLAGS}")


add_executable(coin coinAPI.cpp ./src/jsoncpp.cpp ./src/coinBaseClient.cpp ./src/orderBook.cpp ./src/parser.cpp)
target_link_libraries(coin PRIVATE pthread cpprestsdk::cpprest)

add_executable(testMe ./test/main.cpp ./src/jsoncpp.cpp ./src/orderBook.cpp ./src/coinBaseClient.cpp)
target_link_libraries(testMe benchmark::benchmark pthread cpprestsdk::cpprest)