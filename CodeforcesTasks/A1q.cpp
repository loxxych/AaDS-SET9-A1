//
// Created by loxxy on 24.05.2026.
//

#include <iostream>
#include <vector>
#include <string>
#include <utility>

class StringQuickSort {
private:
    static int charAt(const std::string& s, int d) {
        if (d >= s.size()) {
            return -1;
        }

        return static_cast<unsigned char>(s[d]);
    }

    static void sort(std::vector<std::string>& arr, int left, int right, int d) {
        if (left >= right) {
            return;
        }

        int lt = left;
        int gt = right;

        int pivot = charAt(arr[left], d);

        int i = left + 1;

        while (i <= gt) {
            int current = charAt(arr[i], d);

            if (current < pivot) {
                std::swap(arr[lt], arr[i]);
                ++lt;
                ++i;
            } else if (current > pivot) {
                std::swap(arr[i], arr[gt]);
                --gt;
            } else {
                ++i;
            }
        }

        sort(arr, left, lt - 1, d);

        if (pivot != -1) {
            sort(arr, lt, gt, d + 1);
        }

        sort(arr, gt + 1, right, d);
    }

public:
    static void sort(std::vector<std::string>& arr) {
        if (arr.empty()) {
            return;
        }

        sort(arr, 0, arr.size() - 1, 0);
    }
};

int main() {
    int n;
    std::cin >> n;

    std::vector<std::string> strings(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> strings[i];
    }

    StringQuickSort::sort(strings);

    for (const auto& s : strings) {
        std::cout << s << '\n';
    }

}