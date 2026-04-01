#include "BinPacker.hpp"
#include <iostream>
#include <fstream>

using namespace std;

bool loadItems(string filename, vector<double>& validItems) {
    ifstream infile(filename);
    if (!infile) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }
    int numItemsToRead;
    if (!(infile >> numItemsToRead)) return false;

    double itemSize;
    int itemsProcessed = 0;
    while (itemsProcessed < numItemsToRead && infile >> itemSize) {
        if (itemSize > 0.0 && itemSize <= 1.0) {
            validItems.push_back(itemSize);
        }
        itemsProcessed++;
    }
    infile.close();
    return true;
}

bool perm1(int s[], int numElements) {
    int m, k, p, q;
    m = numElements - 2;
    while (m >= 0 && s[m] > s[m+1]) { m = m - 1; }
    if (m < 0) return false;

    k = numElements - 1;
    while (s[m] > s[k]) { k = k - 1; }
    swap(s[m], s[k]);

    p = m + 1;
    q = numElements - 1;
    while (p < q) {
        swap(s[p], s[q]);
        p++;
        q--;
    }
    return true;
}

int findOptimalBins(const vector<double>& items) {
    int numElements = items.size();
    int* s = new int[numElements];
    for (int i = 0; i < numElements; i++) { s[i] = i; }

    int minBins = numElements; 
    do {
        int currentBins = 1;
        double currentCapacity = 1.0;
        for (int i = 0; i < numElements; i++) {
            double item = items[s[i]];
            if (currentCapacity >= item) {
                currentCapacity -= item;
            } else {
                currentBins++;
                currentCapacity = 1.0 - item;
                if (currentBins >= minBins) break; 
            }
        }
        if (currentBins < minBins) {
            minBins = currentBins;
        }
    } while (perm1(s, numElements));
    
    delete[] s;
    return minBins;
}

vector<Bin> onlineFirstFit(const vector<double>& items) {
    vector<Bin> bins;
    for (double item : items) {
        bool placed = false;
        for (Bin& bin : bins) {
            if (bin.remainingCapacity >= item) {
                bin.items.push_back(item);
                bin.remainingCapacity -= item;
                placed = true;
                break; 
            }
        }
        if (!placed) {
            Bin newBin;
            newBin.items.push_back(item);
            newBin.remainingCapacity -= item;
            bins.push_back(newBin);
        }
    }
    return bins;
}

vector<Bin> onlineNextFit(const vector<double>& items) {
    vector<Bin> bins;
    for (double item : items) {
        if (bins.empty() || bins.back().remainingCapacity < item) {
            Bin newBin;
            newBin.items.push_back(item);
            newBin.remainingCapacity -= item;
            bins.push_back(newBin);
        } else {
            bins.back().items.push_back(item);
            bins.back().remainingCapacity -= item;
        }
    }
    return bins;
}

vector<Bin> onlineBestFit(const vector<double>& items) {
    vector<Bin> bins;
    for (double item : items) {
        int bestBinIdx = -1;
        double minSpaceLeft = 2.0; 
        for (size_t i = 0; i < bins.size(); ++i) {
            if (bins[i].remainingCapacity >= item) {
                double spaceLeft = bins[i].remainingCapacity - item;
                if (spaceLeft < minSpaceLeft) {
                    minSpaceLeft = spaceLeft;
                    bestBinIdx = i;
                }
            }
        }
        if (bestBinIdx == -1) {
            Bin newBin;
            newBin.items.push_back(item);
            newBin.remainingCapacity -= item;
            bins.push_back(newBin);
        } else {
            bins[bestBinIdx].items.push_back(item);
            bins[bestBinIdx].remainingCapacity -= item;
        }
    }
    return bins;
}

void printBinContents(string title, const vector<Bin>& bins) {
    cout << title << ":" << endl;
    for (size_t i = 0; i < bins.size(); ++i) {
        cout << "b" << i + 1 << ": ";
        for (size_t j = 0; j < bins[i].items.size(); ++j) {
            cout << bins[i].items[j];
            if (j < bins[i].items.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}