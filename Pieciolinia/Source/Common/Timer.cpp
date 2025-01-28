#include "Timer.h"
#include <chrono>
#include <thread>

Timer::Timer() {
    start_time = std::chrono::high_resolution_clock::now();
}

void Timer::reset() {
    start_time = std::chrono::high_resolution_clock::now();
}

double Timer::elapsedMilliseconds() const {
    return std::chrono::duration<double, std::milli>(
        std::chrono::high_resolution_clock::now() - start_time
    ).count();
}