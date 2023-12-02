#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <fstream>

#include "../../utils/io.h"

// Does a comparison horizontally, keeps chars and indices in tuples
std::vector<std::tuple<char, int>> getInfo(const std::string& str)
{
    std::vector<std::tuple<char, int>> chartuples; 
    int size = str.size();

    if (str[0] < str[1])
    {
        std::tuple<char, int> first{str[0], 0};
        chartuples.push_back(first);
    }

    if (str[size - 1] < str[size - 2])
    {
        std::tuple<char, int> last{str[size - 1], size - 1};
        chartuples.push_back(last);
    }

    for (int i = 1; i < size - 1; i++)
    {
        if (str[i] < str[i+1] && str[i] < str[i-1])
        {
            std::tuple<char, int> tp{str[i], i};
            chartuples.push_back(tp);
        } 
    }

    return chartuples;
}

std::vector<char> getLowPoints(
    std::vector<std::vector<std::tuple<char, int>>> info,
    std::vector<std::string> ref
)
{
    std::vector<char> lowPoints;
    int size = info.size();

    for (const auto& tup : info[0])
    {
        auto [first, second] = tup;
        if (first < ref[1][second])
        {
            lowPoints.push_back(first);
        }
    }

    for (const auto& tup : info[size-1])
    {
        auto [first, second] = tup;
        if (first < ref[size-2][second])
        {
            lowPoints.push_back(first);
        }
    }

    for (int i = 1; i < info.size() - 1; i++)
    {
        for (const auto& tup : info[i])
        {
            auto [first, second] = tup;
            if (first < ref[i-1][second] && first < ref[i+1][second] )
            {
                lowPoints.push_back(first);
            }
        }
    }
    return lowPoints;
}


int main()
{
    std::vector<std::string> lines = aoc::ReadLines("../puzzles/day9/input.txt");
    std::vector<std::vector<std::tuple<char, int>>> info;

    for (const std::string& line : lines)
    {
        std::vector<std::tuple<char, int>> lineTuples = getInfo(line);
        info.push_back(lineTuples);
    }

    std::vector<char> lowPoints = getLowPoints(info, lines);

    int total = 0;
    for (const auto& c : lowPoints)
    {
        int val = c - '0' + 1;
        total += val;
    }

    std::cout << total << std::endl;

    return 0;
}