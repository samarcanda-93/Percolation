CXX = g++
CXXFLAGS = -std=c++23 -O2 -Wall -Wextra
TARGET = PercolationStats
OBJS = Percolation.o PercolationStats.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

Percolation.o: Percolation.cpp Percolation.hpp
	$(CXX) $(CXXFLAGS) -c Percolation.cpp

PercolationStats.o: PercolationStats.cpp PercolationStats.hpp Percolation.hpp Stopwatch.hpp
	$(CXX) $(CXXFLAGS) -c PercolationStats.cpp

main.o: main.cpp PercolationStats.hpp Stopwatch.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
