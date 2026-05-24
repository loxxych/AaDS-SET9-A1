//
// Created by loxxy on 24.05.2026.
//

#ifndef SET9_A1_RADIXSORTER_H
#define SET9_A1_RADIXSORTER_H

#include <string>
#include <vector>

class RadixSorter {
private:
    long long charComparisons = 0;
    static const int ALPHABET_SIZE = 74;

    int charAt(const std::string& s, int d);
    void msdRadixSort(std::vector<std::string>& arr, int left, int right, int d);
    void msdRadixSortWithQuickSwitch(std::vector<std::string>& arr, int left, int right, int d);
    void quickSortRecursive(std::vector<std::string>& arr, int left, int right, int d);

public:
    std::vector<std::string> sort(std::vector<std::string> arr);
    std::vector<std::string> sortWithQuickSwitch(std::vector<std::string> arr);

    void resetCharComparisons();
    long long getCharComparisons() const;
};

#endif // SET9_A1_RADIXSORTER_H