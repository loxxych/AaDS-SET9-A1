//
// Created by loxxy on 24.05.2026.
//

#ifndef SET9_A1_MERGESORTER_H
#define SET9_A1_MERGESORTER_H

#include <string>
#include <vector>

class MergeSorter {
private:
    long long charComparisons = 0;

    struct CompareResult {
        int cmp;
        int lcp;
    };

    struct SortedBlock {
        std::vector<std::string> data;
        std::vector<int> lcp;
    };

    int compareStrings(const std::string& a, const std::string& b);
    void standardMergeSortRecursive(std::vector<std::string>& arr, std::vector<std::string>& buffer, int left, int right);
    CompareResult lcpCompare(const std::string& a, const std::string& b, int start);
    SortedBlock mergeBlocks(const SortedBlock& left, const SortedBlock& right);
    SortedBlock stringMergeSortRecursive(const std::vector<std::string>& strings, int left, int right);

public:
    std::vector<std::string> standardSort(std::vector<std::string> arr);
    std::vector<std::string> stringSort(std::vector<std::string> arr);

    void resetCharComparisons();
    long long getCharComparisons() const;
};

#endif //SET9_A1_MERGESORTER_H
