//
// Created by loxxy on 24.05.2026.
//

#include <iostream>
#include <vector>
#include <string>

struct CompareResult {
    int cmp;
    int lcp;
};

CompareResult lcpCompare(const std::string& a, const std::string& b, const int start) {
    int i = start;

    while (i < a.size() && i < b.size() && a[i] == b[i]) {
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

struct SortedBlock {
    std::vector<std::string> data;
    std::vector<int> lcp;
};

SortedBlock mergeBlocks(const SortedBlock& left, const SortedBlock& right) {
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

SortedBlock mergeSort(const std::vector<std::string>& strings, const int left, const int right) {
    if (right - left == 1) {
        return {{strings[left]}, {0}};
    }

    int mid = left + (right - left) / 2;

    const SortedBlock leftPart = mergeSort(strings, left, mid);
    const SortedBlock rightPart = mergeSort(strings, mid, right);

    return mergeBlocks(leftPart, rightPart);
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::string> strings(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> strings[i];
    }

    if (n == 0) {
        return 0;
    }

    SortedBlock sorted = mergeSort(strings, 0, n);

    for (const auto& s : sorted.data) {
        std::cout << s << "\n";
    }
}