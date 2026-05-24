//
// Created by loxxy on 24.05.2026.
//

#include "QuickSorter.h"

int QuickSorter::charAt(const std::string& s, int d) {
    if (d >= s.size()) {
        return -1;
    }

    return static_cast<unsigned char>(s[d]);
}

int QuickSorter::compareStrings(const std::string& a, const std::string& b) {
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

void QuickSorter::standardQuickSortRecursive(std::vector<std::string>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;
    const std::string pivot = arr[left];

    while (i <= j) {
        while (compareStrings(arr[i], pivot) < 0) {
            ++i;
        }

        while (compareStrings(arr[j], pivot) > 0) {
            --j;
        }

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    }

    if (left < j) {
        standardQuickSortRecursive(arr, left, j);
    }

    if (i < right) {
        standardQuickSortRecursive(arr, i, right);
    }
}

void QuickSorter::stringQuickSortRecursive(std::vector<std::string>& arr, int left, int right, int d) {
    if (left >= right) {
        return;
    }

    int lt = left;
    int gt = right;

    int pivot = charAt(arr[left], d);

    int i = left + 1;

    while (i <= gt) {
        int current = charAt(arr[i], d);

        ++charComparisons;
        if (current < pivot) {
            std::swap(arr[lt], arr[i]);
            ++lt;
            ++i;
        } else {
            ++charComparisons;
            if (current > pivot) {
                std::swap(arr[i], arr[gt]);
                --gt;
            } else {
                ++i;
            }
        }
    }

    stringQuickSortRecursive(arr, left, lt - 1, d);

    if (pivot != -1) {
        stringQuickSortRecursive(arr, lt, gt, d + 1);
    }

    stringQuickSortRecursive(arr, gt + 1, right, d);
}

std::vector<std::string> QuickSorter::standardSort(std::vector<std::string> arr) {
    if (arr.empty()) {
        return arr;
    }

    standardQuickSortRecursive(arr, 0, arr.size() - 1);

    return arr;
}

std::vector<std::string> QuickSorter::stringSort(std::vector<std::string> arr) {
    if (arr.empty()) {
        return arr;
    }

    stringQuickSortRecursive(arr, 0, arr.size() - 1, 0);

    return arr;
}

void QuickSorter::resetCharComparisons() {
    charComparisons = 0;
}

long long QuickSorter::getCharComparisons() const {
    return charComparisons;
}
