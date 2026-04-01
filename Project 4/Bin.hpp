#ifndef BIN_HPP
#define BIN_HPP
#include <vector>

struct Bin {
    double remainingCapacity = 1.0;
    std::vector<double> items;
};

#endif