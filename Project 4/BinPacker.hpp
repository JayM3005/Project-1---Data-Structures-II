#ifndef BINPACKER_HPP
#define BINPACKER_HPP

#include <vector>
#include <string>
#include "Bin.hpp"

// Function declarations
bool loadItems(std::string filename, std::vector<double>& validItems);
bool perm1(int s[], int numElements);
int findOptimalBins(const std::vector<double>& items);
std::vector<Bin> onlineFirstFit(const std::vector<double>& items);
std::vector<Bin> onlineNextFit(const std::vector<double>& items);
std::vector<Bin> onlineBestFit(const std::vector<double>& items);
void printBinContents(std::string title, const std::vector<Bin>& bins);

#endif