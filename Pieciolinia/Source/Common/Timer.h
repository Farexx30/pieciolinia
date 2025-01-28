#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

class Timer {
public:
    Timer();

    //Method which resetes time
    void reset();

    //Method which returns time in Miliseconds
    double elapsedMilliseconds() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

#endif 