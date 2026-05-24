//
// Created by loxxy on 24.05.2026.
//

#include <iostream>
#include <vector>
#include <string>

class RadixSorter {
private:
    int charAt(const std::string& s, int d) {
        if (d >= s.size()) {
            return -1;
        }

        return static_cast<unsigned char>(s[d]);
    }

    void msdRadixSort(std::vector<std::string>& arr, int left, int right, int d) {
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

public:
    std::vector<std::string> sort(std::vector<std::string> arr) {
        if (arr.empty()) {
            return arr;
        }

        msdRadixSort(arr, 0, arr.size() - 1, 0);

        return arr;
    }
};

int main() {
    int n;
    std::cin >> n;

    std::vector<std::string> strings(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> strings[i];
    }

    RadixSorter sorter;
    strings = sorter.sort(strings);

    for (const auto& s : strings) {
        std::cout << s << "\n";
    }
}