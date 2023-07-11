#include <iostream>
#include <string>
#include <vector>

#include "../../utils/io.h"

int main(int argc, char** argv)
{
  std::vector<std::string> lines = aoc::ReadLines(argv[1]);
  std::vector<int> depths = aoc::ParseIntegers(lines);
  int count = 0;
  for (auto iter = depths.begin() + 4; iter != depths.end(); ++iter) {
    const int prev = *(iter - 3) + *(iter - 2) + *(iter - 1);
    const int curr = *(iter - 2) + *(iter - 1) + *(iter);
    if (curr > prev) count++;
  }
  std::cout << count << "\n";
  return 0;
}