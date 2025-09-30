#include "PercolationStats.hpp"

#include <algorithm>
#include <cmath>
#include <random>
#include <ranges>
#include <vector>

#include "Percolation.hpp"

PercolationStats::PercolationStats(size_t _n, size_t _trials)
    : n(_n), trials(_trials) {
  thresholds.reserve(trials);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, static_cast<int>(n) - 1);
  for (size_t trial = 0; trial < trials; trial++) {
    Percolation perc(n);
    // Create list of all possible sites
    auto sites = std::views::cartesian_product(std::views::iota(0uz, n),
                                               std::views::iota(0uz, n)) |
                 std::ranges::to<std::vector>();
    // WITHOUT RANGES
    // for (size_t row = 0; row < n; row++) {
    //   for (size_t col = 0; col < n; col++) {
    //     sites.emplace_back(row, col);
    //   }
    // }
    // Randomize the order
    std::shuffle(sites.begin(), sites.end(), gen);

    // Open sites until percolation occurs
    for (const auto& [row, col] : sites) {
      perc.open(row, col);
      if (perc.percolates()) {
        double threshold = static_cast<double>(perc.numberOfOpenSites()) /
                           static_cast<double>(n * n);
        thresholds.emplace_back(threshold);
        break;  // Stop immediately when percolation occurs
      }
    }
  }
}

double PercolationStats::mean() {
  return std::ranges::fold_left(thresholds, 0.0, std::plus{}) /
         static_cast<double>(trials);
}

double PercolationStats::stddev() {
  if (trials <= 1) return 0;

  double m = mean();

  // for (double threshold : thresholds) {
  //   double diff = threshold - m;
  //   sum_squared_diff += pow(diff, 2);
  // }
  // return std::sqrt(sum_squared_diff / static_cast<double>(trials - 1));

  auto squared_diffs = thresholds | std::views::transform([m](double t) {
                         return std::pow(t - m, 2);
                       });
  double sum_squared_diff =
      std::ranges::fold_left(squared_diffs, 0.0, std::plus{});
  return std::sqrt(sum_squared_diff / static_cast<double>(trials - 1));
}

double PercolationStats::confidenceLo() {
  return mean() - 1.96 * stddev() / std::sqrt(trials);
}

double PercolationStats::confidenceHi() {
  return mean() + 1.96 * stddev() / std::sqrt(trials);
}
