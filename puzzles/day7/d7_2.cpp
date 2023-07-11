#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

#include "../../utils/io.h"

int median(std::vector<int> values)
{
    int pos = round(values.size() / 2);
    std::sort(values.begin(), values.end());
    return values[pos];
}

int average(std::vector<int> values)
{
    return round(std::accumulate(values.begin(), values.end(), 0) / values.size());
}

int main(int argc, char** argv)
{
    std::vector<std::string> crabsStr = aoc::ReadCommaDelimitedFile(argv[1]);

    std::vector<int> crabs;
    for (std::string& str : crabsStr)
    {
        int pos = std::stoi(str);
        crabs.push_back(pos);
    }

    int med = median(crabs);
    int avg = average(crabs);

    int res1 = 0;
    int res2 = 0;
    for (auto& crab : crabs)
    {
        res1 += abs(crab - med);

        int factor = 1;
        for (int i = abs(crab - avg); i > 0; i--)
        {
            res2 += factor;
            factor++;
        }
    }

    std::cout << res1 << "\n";
    std::cout << res2 << "\n";

    return 0;
}