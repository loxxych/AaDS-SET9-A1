//
// Created by loxxy on 24.05.2026.
//

#ifndef SET9_A1_QUICKSORTER_H
#define SET9_A1_QUICKSORTER_H

#include <string>
#include <vector>

class QuickSorter {
private:
    long long charComparisons = 0;

    int charAt(const std::string& s, int d);
    int compareStrings(const std::string& a, const std::string& b);
    void standardQuickSortRecursive(std::vector<std::string>& arr, int left, int right);
    void stringQuickSortRecursive(std::vector<std::string>& arr, int left, int right, int d);

public:
    std::vector<std::string> standardSort(std::vector<std::string> arr);
    std::vector<std::string> stringSort(std::vector<std::string> arr);

    void resetCharComparisons();
    long long getCharComparisons() const;
};

#endif //SET9_A1_QUICKSORTER_H
