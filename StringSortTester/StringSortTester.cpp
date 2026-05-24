//
// Created by loxxy on 24.05.2026.
//

#include "StringSortTester.h"

#include <chrono>
#include <fstream>
#include <stdexcept>
#include <filesystem>

StringSortTester::StringSortTester(int stringSize, int repeats, int minArraySize, int maxArraySize, int step) {
    this->stringSize = stringSize;
    this->repeats = repeats;
    this->minArraySize = minArraySize;
    this->maxArraySize = maxArraySize;
    this->step = step;
}

std::vector<std::string> StringSortTester::getSubArray(const std::vector<std::string>& arr, int size) {
    return std::vector<std::string>(arr.begin(), arr.begin() + size);
}

std::vector<std::string> StringSortTester::runSort(const std::vector<std::string>& arr, const std::string& algorithmName) {
    if (algorithmName == "StandardMergeSort") {
        return mergeSorter.standardSort(arr);
    }

    if (algorithmName == "StandardQuickSort") {
        return quickSorter.standardSort(arr);
    }

    if (algorithmName == "StringMergeSort") {
        return mergeSorter.stringSort(arr);
    }

    if (algorithmName == "StringQuickSort") {
        return quickSorter.stringSort(arr);
    }

    if (algorithmName == "RadixSort") {
        return radixSorter.sort(arr);
    }

    if (algorithmName == "RadixSortWithQuickSwitch") {
        return radixSorter.sortWithQuickSwitch(arr);
    }

    throw std::invalid_argument("Unknown sorting algorithm: " + algorithmName);
}

void StringSortTester::resetComparisons(const std::string& algorithmName) {
    if (algorithmName == "StandardMergeSort" || algorithmName == "StringMergeSort") {
        mergeSorter.resetCharComparisons();
        return;
    }

    if (algorithmName == "StandardQuickSort" || algorithmName == "StringQuickSort") {
        quickSorter.resetCharComparisons();
        return;
    }

    if (algorithmName == "RadixSort" || algorithmName == "RadixSortWithQuickSwitch") {
        radixSorter.resetCharComparisons();
        return;
    }

    throw std::invalid_argument("Unknown sorting algorithm: " + algorithmName);
}

long long StringSortTester::getComparisons(const std::string& algorithmName) {
    if (algorithmName == "StandardMergeSort" || algorithmName == "StringMergeSort") {
        return mergeSorter.getCharComparisons();
    }

    if (algorithmName == "StandardQuickSort" || algorithmName == "StringQuickSort") {
        return quickSorter.getCharComparisons();
    }

    if (algorithmName == "RadixSort" || algorithmName == "RadixSortWithQuickSwitch") {
        return radixSorter.getCharComparisons();
    }

    throw std::invalid_argument("Unknown sorting algorithm: " + algorithmName);
}

StringSortTester::MeasurementResult StringSortTester::measureAverage(const std::vector<std::string>& arr, const std::string& algorithmName) {
    double totalTime = 0.0;
    long long totalComparisons = 0;

    for (int i = 0; i < repeats; ++i) {
        auto copy = arr;

        resetComparisons(algorithmName);

        auto start = std::chrono::high_resolution_clock::now();
        runSort(copy, algorithmName);
        auto finish = std::chrono::high_resolution_clock::now();

        auto time = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        totalTime += static_cast<double>(time);
        totalComparisons += getComparisons(algorithmName);
    }

    return {totalTime / repeats, totalComparisons / repeats};
}

void StringSortTester::writeResultsToCsv(const std::vector<TestResult>& results, const std::string& fileName) {
    std::filesystem::create_directories("TestResults");
    std::string fullPath = "../TestResults/" + fileName;

    std::ofstream out(fullPath);

    out << "algorithm,data_type,array_size,max_string_size,average_time_microseconds,average_char_comparisons\n";

    for (const auto& result : results) {
        out << result.algorithmName << ","
            << result.dataType << ","
            << result.arraySize << ","
            << result.stringSize << ","
            << result.averageTimeMicroseconds << ","
            << result.averageCharComparisons << "\n";
    }
}

void StringSortTester::runAllTests(const std::string& outputFileName) {
    std::vector<TestResult> results;

    std::vector<std::string> randomArray = generator.generateRandom(stringSize, maxArraySize);
    std::vector<std::string> reversedArray = generator.generateRevSorted(stringSize, maxArraySize);
    std::vector<std::string> almostSortedArray = generator.generateAlmostSorted(stringSize, maxArraySize);

    std::vector<std::string> algorithms = {
        "StandardMergeSort",
        "StandardQuickSort",
        "StringMergeSort",
        "StringQuickSort",
        "RadixSort",
        "RadixSortWithQuickSwitch"
    };

    for (int currentSize = minArraySize; currentSize <= maxArraySize; currentSize += step) {
        std::vector<std::string> randomSubArray = getSubArray(randomArray, currentSize);
        std::vector<std::string> reversedSubArray = getSubArray(reversedArray, currentSize);
        std::vector<std::string> almostSortedSubArray = getSubArray(almostSortedArray, currentSize);

        for (const auto& algorithmName : algorithms) {
            MeasurementResult randomResult = measureAverage(randomSubArray, algorithmName);
            results.push_back({algorithmName, "random", currentSize, stringSize, randomResult.averageTimeMicroseconds, randomResult.averageCharComparisons});

            MeasurementResult reversedResult = measureAverage(reversedSubArray, algorithmName);
            results.push_back({algorithmName, "reversed", currentSize, stringSize, reversedResult.averageTimeMicroseconds, reversedResult.averageCharComparisons});

            MeasurementResult almostSortedResult = measureAverage(almostSortedSubArray, algorithmName);
            results.push_back({algorithmName, "almost_sorted", currentSize, stringSize, almostSortedResult.averageTimeMicroseconds, almostSortedResult.averageCharComparisons});
        }
    }

    writeResultsToCsv(results, outputFileName);
}
