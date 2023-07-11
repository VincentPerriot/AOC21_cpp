#include <iostream>
#include <string>
#include <vector>

#include "../../utils/io.h"

bool GammaBit(std::vector<int> numbers, int pos){

    int one_count = 0;
    const int mask = 1 << pos;

    for (const int num : numbers)
    {
        if ((mask & num) != 0) one_count++;
    }
    return (one_count >= (numbers.size() / 2));
}

int main(int argc, char** argv)
{
    std::vector<std::string> lines = aoc::ReadLines(argv[1]);
    std::vector<int> values = aoc::ParseIntegers(lines, 2);

    int gamma = 0;
    for (int pos = 0; pos < 12; pos++)
    {
        if (GammaBit(values, pos)) {
            // this will set
            gamma |= (1 << pos);
        }
    }
    // Inverse of Gamma up to lower 12 bits
    const int epsilon = ~gamma & ((1 << 12) - 1);

    std::cout << (gamma * epsilon) << std::endl;

    return 0;
}