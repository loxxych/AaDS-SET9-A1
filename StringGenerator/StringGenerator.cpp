//
// Created by loxxy on 24.05.2026.
//

#include "StringGenerator.h"

#include <algorithm>
#include <stdexcept>

StringGenerator::StringGenerator(int seed) : generator(seed) {}

std::string StringGenerator::generateChars(int stringSize) {
    std::uniform_int_distribution<int> charDistribution(0, static_cast<int>(alphabet.size()) - 1);

    std::string result;
    result.reserve(stringSize);

    for (int i = 0; i < stringSize; ++i) {
        result += alphabet[charDistribution(generator)];
    }

    return result;
}

std::string StringGenerator::generateString(int maxStringSize) {
    if (maxStringSize < 10 || maxStringSize > 200) {
        throw std::invalid_argument("Максимальный размер строки должен быть в пределах [10, 200]");
    }

    std::uniform_int_distribution<int> lengthDistribution(10, maxStringSize);

    return generateChars(lengthDistribution(generator));
}

std::vector<std::string> StringGenerator::generateRandom(int maxStringSize, int arraySize) {
    if (arraySize < 100 || arraySize > 3000) {
        throw std::invalid_argument("Размер массива должен быть в пределах [100, 3000]");
    }

    std::vector<std::string> result;
    result.reserve(arraySize);

    for (int i = 0; i < arraySize; ++i) {
        result.push_back(generateString(maxStringSize));
    }

    return result;
}

std::vector<std::string> StringGenerator::generateRevSorted(int maxStringSize, int arraySize) {
    std::vector<std::string> result = generateRandom(maxStringSize, arraySize);

    std::sort(result.begin(), result.end(), std::greater<std::string>());

    return result;
}

std::vector<std::string> StringGenerator::generateAlmostSorted(int maxStringSize, int arraySize, int swapsCount) {
    std::vector<std::string> result = generateRandom(maxStringSize, arraySize);

    std::sort(result.begin(), result.end());

    if (swapsCount < 0) {
        swapsCount = std::max(1, arraySize / 20);
    }

    std::uniform_int_distribution<int> indexDistribution(0, arraySize - 1);

    for (int i = 0; i < swapsCount; ++i) {
        int first = indexDistribution(generator);
        int second = indexDistribution(generator);

        std::swap(result[first], result[second]);
    }

    return result;
}

std::vector<std::string> StringGenerator::generateWithCommonPrefix(int maxStringSize, int arraySize, int prefixLength) {
    if (maxStringSize < 10 || maxStringSize > 200) {
        throw std::invalid_argument("Максимальный размер строки должен быть в пределах [10, 200]");
    }

    if (prefixLength < 0 || prefixLength > maxStringSize) {
        throw std::invalid_argument("Длина префикса должна быть в пределах [0, maxStringSize]");
    }

    std::vector<std::string> result;
    result.reserve(arraySize);

    std::string prefix = generateChars(prefixLength);
    std::uniform_int_distribution<int> lengthDistribution(std::max(10, prefixLength), maxStringSize);

    for (int i = 0; i < arraySize; ++i) {
        int totalLength = lengthDistribution(generator);
        std::string suffix = generateChars(totalLength - prefixLength);

        result.push_back(prefix + suffix);
    }

    return result;
}
