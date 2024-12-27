/*
  ==============================================================================

    Timer.cpp
    Created: 27 Dec 2024 9:22:15am
    Author:  Lenovo

  ==============================================================================
*/

#include "Timer.h"
#include <chrono>
#include <thread>


class Timer {
public:

    Timer() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};