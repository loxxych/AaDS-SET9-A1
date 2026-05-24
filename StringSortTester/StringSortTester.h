//
// Created by loxxy on 24.05.2026.
//

#ifndef SET9_A1_STRINGSORTTESTER_H
#define SET9_A1_STRINGSORTTESTER_H

#include "../StringGenerator/StringGenerator.h"
#include "../StringSort/MergeSort/MergeSorter.h"
#include "../StringSort/QuickSort/QuickSorter.h"
#include "../StringSort/RadixSort/RadixSorter.h"

#include <string>
#include <vector>

class StringSortTester {
private:
    struct TestResult {
        std::string algorithmName;
        std::string dataType;
        int arraySize;
        int stringSize;
        double averageTimeMicroseconds;
        long long averageCharComparisons;
    };

    struct MeasurementResult {
        double averageTimeMicroseconds;
        long long averageCharComparisons;
    };

    int minArraySize;
    int maxArraySize;
    int step;
    int repeats;
    int stringSize;

    StringGenerator generator;
    MergeSorter mergeSorter;
    QuickSorter quickSorter;
    RadixSorter radixSorter;

    std::vector<std::string> getSubArray(const std::vector<std::string>& arr, int size);
    std::vector<std::string> runSort(const std::vector<std::string>& arr, const std::string& algorithmName);
    MeasurementResult measureAverage(const std::vector<std::string>& arr, const std::string& algorithmName);

    void resetComparisons(const std::string& algorithmName);
    long long getComparisons(const std::string& algorithmName);

    void writeResultsToCsv(const std::vector<TestResult>& results, const std::string& fileName);

public:
    StringSortTester(int stringSize = 100, int repeats = 10, int minArraySize = 100, int maxArraySize = 3000, int step = 100);

    void runAllTests(const std::string& outputFileName);
};

#endif // SET9_A1_STRINGSORTTESTER_H