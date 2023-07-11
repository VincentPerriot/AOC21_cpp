#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include "../../utils/io.h"

bool CommonBit(std::vector<int> numbers, int pos, bool most_common){

    int one_count = 0;
    const int mask = 1 << pos;

    for (const int num : numbers)
    {
        if ((mask & num) != 0) one_count++;
    }

    if (most_common){
        return one_count >= std::ceil(numbers.size() / 2.0);
    } else {
        return one_count < std::ceil(numbers.size() / 2.0);
    }
}

int Filter(std::vector<int> numbers, bool most_common)
{
    // Store all most common in an an int like Gamma from part1
    for (int pos = 11; pos >= 0; pos--)
    {
        const int mcb = CommonBit(numbers, pos, most_common) * (1 << pos);
        std::vector<int> filtered;
        for (int num : numbers)
        {
            if ((num & ( 1 << pos )) == mcb)
                filtered.push_back(num);
        }
        if (filtered.size() == 1)
            return filtered.front();

        numbers = std::move(filtered);
    }
    // In case we have more than 1 num passing the test
    return numbers.front();
}

int main(int argc, char** argv)
{
    std::vector<std::string> lines = aoc::ReadLines(argv[1]);
    std::vector<int> values = aoc::ParseIntegers(lines, 2);

    int val = Filter(values, true);
    int val2 = Filter(values, false);

    std::cout << val << std::endl;
    std::cout << val2 << std::endl;

    std::cout << (val * val2) << std::endl;

    return 0;
}