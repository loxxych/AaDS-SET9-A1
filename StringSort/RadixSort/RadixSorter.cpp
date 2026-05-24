//
// Created by loxxy on 24.05.2026.
//

#include "RadixSorter.h"

int RadixSorter::charAt(const std::string& s, int d) {
    if (d >= s.size()) {
        return -1;
    }

    return static_cast<unsigned char>(s[d]);
}

void RadixSorter::quickSortRecursive(std::vector<std::string>& arr, int left, int right, int d) {
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

    quickSortRecursive(arr, left, lt - 1, d);

    if (pivot != -1) {
        quickSortRecursive(arr, lt, gt, d + 1);
    }

    quickSortRecursive(arr, gt + 1, right, d);
}

void RadixSorter::msdRadixSort(std::vector<std::string>& arr, int left, int right, int d) {
    if (left >= right) {
        return;
    }

    const int radix = 256;

    std::vector<int> count(radix + 2, 0);
    std::vector<std::string> aux(right - left + 1);

    for (int i = left; i <= right; ++i) {
        int c = charAt(arr[i], d);
        ++count[c + 2];
    }

    for (int r = 0; r < radix + 1; ++r) {
        count[r + 1] += count[r];
    }

    std::vector<int> borders = count;

    for (int i = left; i <= right; ++i) {
        int c = charAt(arr[i], d);
        aux[count[c + 1]++] = arr[i];
    }

    for (int i = left; i <= right; ++i) {
        arr[i] = aux[i - left];
    }

    for (int r = 1; r < radix + 1; ++r) {
        int subLeft = left + borders[r];
        int subRight = left + borders[r + 1] - 1;

        if (subLeft < subRight) {
            msdRadixSort(arr, subLeft, subRight, d + 1);
        }
    }
}

void RadixSorter::msdRadixSortWithQuickSwitch(std::vector<std::string>& arr, int left, int right, int d) {
    if (left >= right) {
        return;
    }

    if (right - left + 1 < ALPHABET_SIZE) {
        quickSortRecursive(arr, left, right, d);
        return;
    }

    const int radix = 256;

    std::vector<int> count(radix + 2, 0);
    std::vector<std::string> aux(right - left + 1);

    for (int i = left; i <= right; ++i) {
        int c = charAt(arr[i], d);
        ++count[c + 2];
    }

    for (int r = 0; r < radix + 1; ++r) {
        count[r + 1] += count[r];
    }

    std::vector<int> borders = count;

    for (int i = left; i <= right; ++i) {
        int c = charAt(arr[i], d);
        aux[count[c + 1]++] = arr[i];
    }

    for (int i = left; i <= right; ++i) {
        arr[i] = aux[i - left];
    }

    for (int r = 1; r < radix + 1; ++r) {
        int subLeft = left + borders[r];
        int subRight = left + borders[r + 1] - 1;

        if (subLeft < subRight) {
            msdRadixSortWithQuickSwitch(arr, subLeft, subRight, d + 1);
        }
    }
}

std::vector<std::string> RadixSorter::sort(std::vector<std::string> arr) {
    if (arr.empty()) {
        return arr;
    }

    msdRadixSort(arr, 0, arr.size() - 1, 0);

    return arr;
}

std::vector<std::string> RadixSorter::sortWithQuickSwitch(std::vector<std::string> arr) {
    if (arr.empty()) {
        return arr;
    }

    msdRadixSortWithQuickSwitch(arr, 0, arr.size() - 1, 0);

    return arr;
}

void RadixSorter::resetCharComparisons() {
    charComparisons = 0;
}

long long RadixSorter::getCharComparisons() const {
    return charComparisons;
}
