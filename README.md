# Percolation

A C++23 implementation of the Percolation problem using the Union-Find algorithm.

## Overview

This project models a percolation system using an n-by-n grid of sites. Each site is either open or blocked. The system percolates if there is a path of open sites from the top row to the bottom row.

## Problem Description

See the [official specification](https://coursera.cs.princeton.edu/algs4/assignments/percolation/specification.php) for complete details.

## Requirements

- C++23 compatible compiler

## Files

- **[Percolation.hpp](Percolation.hpp)** / **[Percolation.cpp](Percolation.cpp)** - Core percolation data structure
- **[PercolationStats.hpp](PercolationStats.hpp)** / **[PercolationStats.cpp](PercolationStats.cpp)** - Monte Carlo simulation for percolation threshold estimation
- **[Stopwatch.hpp](Stopwatch.hpp)** - Timing utility
- **[main.cpp](main.cpp)** - Entry point

## Building

Using the provided [Makefile](Makefile):

```bash
make
```

Or manually:

```bash
g++ -std=c++23 -O2 main.cpp Percolation.cpp PercolationStats.cpp -o percolation
```

## Usage

```bash
./percolation <grid_size> <num_trials>
```

Example:
```bash
./percolation 200 100
```
