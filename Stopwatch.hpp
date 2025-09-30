#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>

class Stopwatch {
public:
    Stopwatch() : start_time(std::chrono::high_resolution_clock::now()) {}

    // Returns elapsed time in seconds
    double elapsedTime() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;
        return elapsed.count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

#endif // STOPWATCH_HPP