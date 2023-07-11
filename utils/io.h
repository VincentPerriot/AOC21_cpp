#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace aoc {

    // Whole file content as string
    std::string ReadFile(const char* filename);

    // Each line is a different string
    std::vector<std::string> ReadLines(const char* filename);

    // Create generic for integers and parse from string
    template <typename IntType = int>
    std::vector<IntType> ParseIntegers(const std::vector<std::string>& strings, int base =10)
    {
        std::vector<IntType> integers(strings.size(), 0);
        for (size_t idx = 0; idx < strings.size(); idx++)
        {
            const int i = std::stoi(strings[idx], 0, base);
            integers[idx] = i;
        }
        return integers;
    }

    template <class InputIt, class T>
    constexpr InputIt find(InputIt first, InputIt last, const T& value)
    {
        for(; first != last; first++)
            if (*first == value)
                return first;
        return last;
    }

    std::vector<std::string> ReadCommaDelimitedFile(const char* filename);

    std::vector<int> ParseWhiteSpace(std::string str);
}