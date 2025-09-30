#ifndef PERCOLATIONSTATS_HPP
#define PERCOLATIONSTATS_HPP

#include <vector>

class PercolationStats {
 public:
  PercolationStats(size_t _n, size_t _trials);
  double mean();
  double stddev();
  double confidenceLo();
  double confidenceHi();

 private:
  size_t n;
  size_t trials;
  std::vector<double> thresholds;
};

#endif  // PERCOLATIONSTATS_HPP
