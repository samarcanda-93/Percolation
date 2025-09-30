#include <iostream>
#include <print>

#include "PercolationStats.hpp"
#include "Stopwatch.hpp"

int main() {
  size_t size, t;
  std::print("Insert grid size : ");
  std::cin >> size;

  std::print("Insert number of trials : ");
  std::cin >> t;

  Stopwatch timer;
  PercolationStats experiment(size, t);
  double elapsed = timer.elapsedTime();

  std::println("mean                    = {:.16f}", experiment.mean());
  std::println("stddev                  = {:.16f}", experiment.stddev());
  std::println("95% confidence interval = [{:.16f}, {:.16f}]",
               experiment.confidenceLo(), experiment.confidenceHi());
  std::println("elapsed time            = {:.4f} seconds", elapsed);

  return 0;
}
