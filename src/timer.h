#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
class Timer{
    std::chrono::high_resolution_clock::time_point _start;
    std::string _task;
    public:
    Timer(std::string task):_start(std::chrono::high_resolution_clock::now()),_task(task){}
    ~Timer(){std::cout<<_task<<" Took: "<<(std::chrono::high_resolution_clock::now()-_start).count()/1000<<" us"<<std::endl;}
};