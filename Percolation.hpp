#ifndef PERCOLATION_HPP
#define PERCOLATION_HPP

#include <limits>
#include <vector>

class Percolation {
 public:
  Percolation(size_t size);
  void open(size_t row, size_t col);
  bool isOpen(size_t row, size_t col);
  bool isFull(size_t row, size_t col);
  int numberOfOpenSites();
  bool percolates();

 private:
  size_t n;
  std::vector<size_t> parent;             // Flat union-find parent array
  std::vector<size_t> tree_size_flat;     // Flat tree size array
  std::vector<std::vector<bool>> status;  // Grid open status

  static constexpr size_t VIRTUAL_TOP = std::numeric_limits<size_t>::max() - 1;
  static constexpr size_t VIRTUAL_BOTTOM = std::numeric_limits<size_t>::max();

  size_t toUFIndex(size_t id) const;
  size_t getRoot(size_t id);
  bool isConnected(size_t id1, size_t id2);
  void makeUnion(size_t id1, size_t id2);
};

#endif  // PERCOLATION_HPP
