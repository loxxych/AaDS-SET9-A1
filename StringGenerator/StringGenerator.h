//
// Created by loxxy on 24.05.2026.
//

#ifndef SET9_A1_STRINGGENERATOR_H
#define SET9_A1_STRINGGENERATOR_H

#include <string>
#include <vector>
#include <random>

class StringGenerator {
private:
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-";
    std::mt19937 generator;
    std::string generateChars(int stringSize);
    std::string generateString(int maxStringSize);

public:
    StringGenerator(int seed = std::random_device{}());

    std::vector<std::string> generateRandom(int maxStringSize, int arraySize);
    std::vector<std::string> generateRevSorted(int maxStringSize, int arraySize);
    std::vector<std::string> generateAlmostSorted(int maxStringSize, int arraySize, int swapsCount = -1);
    std::vector<std::string> generateWithCommonPrefix(int maxStringSize, int arraySize, int prefixLength);
};

#endif // SET9_A1_STRINGGENERATOR_H
