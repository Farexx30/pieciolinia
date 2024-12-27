/*
  ==============================================================================

    Timer.h
    Created: 27 Dec 2024 9:22:15am
    Author:  Lenovo

  ==============================================================================
*/

#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

class Timer {
public:

    Timer();

    void reset();

    double elapsedMilliseconds() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

#endif 