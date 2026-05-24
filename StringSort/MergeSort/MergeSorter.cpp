//
// Created by loxxy on 24.05.2026.
//

#include "MergeSorter.h"

int MergeSorter::compareStrings(const std::string& a, const std::string& b) {
    int i = 0;

    while (i < a.size() && i < b.size()) {
        ++charComparisons;

        if (a[i] < b[i]) {
            return -1;
        }

        if (a[i] > b[i]) {
            return 1;
        }

        ++i;
    }

    if (a.size() == b.size()) {
        return 0;
    }

    return a.size() < b.size() ? -1 : 1;
}

void MergeSorter::standardMergeSortRecursive(std::vector<std::string>& arr, std::vector<std::string>& buffer, int left, int right) {
    if (right - left <= 1) {
        return;
    }

    int mid = left + (right - left) / 2;
    standardMergeSortRecursive(arr, buffer, left, mid);
    standardMergeSortRecursive(arr, buffer, mid, right);

    int i = left;
    int j = mid;
    int k = left;

    while (i < mid && j < right) {
        if (compareStrings(arr[i], arr[j]) <= 0) {
            buffer[k++] = arr[i++];
        } else {
            buffer[k++] = arr[j++];
        }
    }

    while (i < mid) {
        buffer[k++] = arr[i++];
    }

    while (j < right) {
        buffer[k++] = arr[j++];
    }

    for (int index = left; index < right; ++index) {
        arr[index] = buffer[index];
    }
}

MergeSorter::CompareResult MergeSorter::lcpCompare(const std::string& a, const std::string& b, const int start) {
    int i = start;

    while (i < a.size() && i < b.size()) {
        ++charComparisons;

        if (a[i] != b[i]) {
            break;
        }

        ++i;
    }

    if (i == a.size() && i == b.size()) {
        return {0, i};
    }

    if (i == b.size()) {
        return {1, i};
    }

    if (i == a.size()) {
        return {-1, i};
    }

    return {a[i] < b[i] ? -1 : 1, i};
}

MergeSorter::SortedBlock MergeSorter::mergeBlocks(const SortedBlock& left, const SortedBlock& right) {
    SortedBlock result;

    int i = 0;
    int j = 0;

    int lcpLeft = 0;
    int lcpRight = 0;

    bool hasLast = false;

    while (i < left.data.size() && j < right.data.size()) {
        bool takeLeft;
        int outputLcp;
        int crossLcp;

        if (!hasLast) {
            CompareResult cmp = lcpCompare(left.data[i], right.data[j], 0);

            takeLeft = cmp.cmp <= 0;
            outputLcp = 0;
            crossLcp = cmp.lcp;
        } else if (lcpLeft > lcpRight) {
            takeLeft = true;
            outputLcp = lcpLeft;
            crossLcp = lcpRight;
        } else if (lcpRight > lcpLeft) {
            takeLeft = false;
            outputLcp = lcpRight;
            crossLcp = lcpLeft;
        } else {
            CompareResult cmp = lcpCompare(left.data[i], right.data[j], lcpLeft);

            takeLeft = cmp.cmp <= 0;
            outputLcp = lcpLeft;
            crossLcp = cmp.lcp;
        }

        if (takeLeft) {
            result.data.push_back(left.data[i]);
            result.lcp.push_back(outputLcp);

            ++i;

            if (i < left.data.size()) {
                lcpLeft = left.lcp[i];
            }

            lcpRight = crossLcp;
        } else {
            result.data.push_back(right.data[j]);
            result.lcp.push_back(outputLcp);

            ++j;

            if (j < right.data.size()) {
                lcpRight = right.lcp[j];
            }

            lcpLeft = crossLcp;
        }

        hasLast = true;
    }

    while (i < left.data.size()) {
        result.data.push_back(left.data[i]);

        if (!hasLast) {
            result.lcp.push_back(0);
        } else {
            result.lcp.push_back(lcpLeft);
        }

        ++i;
        hasLast = true;

        if (i < left.data.size()) {
            lcpLeft = left.lcp[i];
        }
    }

    while (j < right.data.size()) {
        result.data.push_back(right.data[j]);

        if (!hasLast) {
            result.lcp.push_back(0);
        } else {
            result.lcp.push_back(lcpRight);
        }

        ++j;
        hasLast = true;

        if (j < right.data.size()) {
            lcpRight = right.lcp[j];
        }
    }

    return result;
}

MergeSorter::SortedBlock MergeSorter::stringMergeSortRecursive(const std::vector<std::string>& strings, const int left, const int right) {
    if (right - left == 1) {
        return {{strings[left]}, {0}};
    }

    int mid = left + (right - left) / 2;

    const SortedBlock leftPart = stringMergeSortRecursive(strings, left, mid);
    const SortedBlock rightPart = stringMergeSortRecursive(strings, mid, right);

    return mergeBlocks(leftPart, rightPart);
}

std::vector<std::string> MergeSorter::standardSort(std::vector<std::string> arr) {
    std::vector<std::string> buffer(arr.size());
    standardMergeSortRecursive(arr, buffer, 0, arr.size());

    return arr;
}

std::vector<std::string> MergeSorter::stringSort(std::vector<std::string> arr) {
    if (arr.empty()) {
        return arr;
    }

    SortedBlock sorted = stringMergeSortRecursive(arr, 0, arr.size());

    return sorted.data;
}

void MergeSorter::resetCharComparisons() {
    charComparisons = 0;
}

long long MergeSorter::getCharComparisons() const {
    return charComparisons;
}
