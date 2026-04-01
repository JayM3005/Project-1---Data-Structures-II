#include <iostream>
#include <vector>
#include <algorithm>
#include "BinPacker.hpp"

using namespace std;

int main() {
    vector<double> items;

    if (!loadItems("items.txt", items)) {
        return 1;
    }

    cout << "\nCalculating permutations for optimal solution... (Please wait)" << endl;

    int optimalBins = findOptimalBins(items);

    vector<Bin> on_FF_Result = onlineFirstFit(items);
    vector<Bin> on_NF_Result = onlineNextFit(items);
    vector<Bin> on_BF_Result = onlineBestFit(items);

    vector<double> sortedItems = items;
    sort(sortedItems.begin(), sortedItems.end(), greater<double>());

    vector<Bin> off_FF_Result = onlineFirstFit(sortedItems);
    vector<Bin> off_BF_Result = onlineBestFit(sortedItems);

    cout << "\nPolicy\t\t\tTotal Bins Used" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Optimal Solution\t" << optimalBins << endl;
    cout << "Online Algorithm" << endl;
    cout << "  First Fit\t\t" << on_FF_Result.size() << endl;
    cout << "  Next Fit\t\t" << on_NF_Result.size() << endl;
    cout << "  Best Fit\t\t" << on_BF_Result.size() << endl;
    cout << "Offline Algorithm" << endl;
    cout << "  First Fit\t\t" << off_FF_Result.size() << endl;
    cout << "  Best Fit\t\t" << off_BF_Result.size() << endl;
    cout << endl;

    printBinContents("Optimal", off_FF_Result); 
    cout << "..." << endl;
    printBinContents("Online First Fit", on_FF_Result);
    cout << "..." << endl;
    printBinContents("Online Next Fit", on_NF_Result);
    cout << "..." << endl;
    printBinContents("Online Best Fit", on_BF_Result);
    cout << "..." << endl;
    printBinContents("Offline First Fit", off_FF_Result);
    cout << "..." << endl;
    printBinContents("Offline Best Fit", off_BF_Result);
    
    return 0;
}