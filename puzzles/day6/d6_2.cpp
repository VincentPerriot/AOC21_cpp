#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <numeric>
#include <deque>

#include "../../utils/io.h"

int main(int argc, char** argv)
{
    std::vector<std::string> fishStr = aoc::ReadCommaDelimitedFile(argv[1]);

    std::deque<int64_t> fish(9, 0);
    for (std::string& str : fishStr)
    {
        int timer = std::stoi(str);
        ++fish[timer];
    }

    for (int day = 0; day < 256; day++)
    {
        const int64_t zeroes = fish.front();
        fish.pop_front();
        fish[6] += zeroes;
        fish.push_back(zeroes);
    }

    std::cout << std::accumulate(fish.begin(), fish.end(), int64_t{0}) << "\n";

    return 0;
}