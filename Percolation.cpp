#include "Percolation.hpp"

Percolation::Percolation(size_t size)
    : n(size),
      parent(size * size + 2),             // Union-find parent array
      tree_size_flat(size * size + 2, 1),  // Union-find tree sizes
      status(size, std::vector<bool>(size, false)) {
  for (size_t i = 0; i < parent.size(); i++) {
    parent[i] = i;
  }
}

void Percolation::open(size_t row, size_t col) {
  if (status[row][col]) return;
  status[row][col] = true;
  size_t id = row * n + col;

  // Connect to virtual top if in top row
  if (row == 0) makeUnion(id, VIRTUAL_TOP);
  // Connect to virtual bottom if in bottom row
  if (row == n - 1) makeUnion(id, VIRTUAL_BOTTOM);

  // Check adjacent sites and connect if open
  if (row > 0 && isOpen(row - 1, col)) makeUnion(id, (row - 1) * n + col);
  if (row < n - 1 && isOpen(row + 1, col)) makeUnion(id, (row + 1) * n + col);
  if (col > 0 && isOpen(row, col - 1)) makeUnion(id, row * n + (col - 1));
  if (col < n - 1 && isOpen(row, col + 1)) makeUnion(id, row * n + (col + 1));
}

bool Percolation::isOpen(size_t row, size_t col) { return status[row][col]; }

bool Percolation::isFull(size_t row, size_t col) {
  if (!isOpen(row, col)) return false;
  size_t id = row * n + col;
  return getRoot(id) == getRoot(VIRTUAL_TOP);
}

int Percolation::numberOfOpenSites() {
  int count = 0;
  for (size_t row = 0; row < n; row++) {
    for (size_t col = 0; col < n; col++) {
      if (status[row][col]) count++;
    }
  }
  return count;
}

bool Percolation::percolates() {
  return isConnected(VIRTUAL_TOP, VIRTUAL_BOTTOM);
}

// Map special constants to actual union-find indices
size_t Percolation::toUFIndex(size_t id) const {
  if (id == VIRTUAL_TOP) return n * n;
  if (id == VIRTUAL_BOTTOM) return n * n + 1;
  return id;
}

size_t Percolation::getRoot(size_t id) {
  size_t idx = toUFIndex(id);
  if (idx != parent[idx]) {
    parent[idx] = getRoot(parent[idx]);  // Path compression
  }
  return parent[idx];
}

bool Percolation::isConnected(size_t id1, size_t id2) {
  return getRoot(id1) == getRoot(id2);
}

void Percolation::makeUnion(size_t id1, size_t id2) {
  size_t root1 = getRoot(id1);
  size_t root2 = getRoot(id2);
  if (root1 == root2) return;

  if (tree_size_flat[root1] < tree_size_flat[root2]) {
    parent[root1] = root2;
    tree_size_flat[root2] += tree_size_flat[root1];
  } else {
    parent[root2] = root1;
    tree_size_flat[root1] += tree_size_flat[root2];
  }
}
