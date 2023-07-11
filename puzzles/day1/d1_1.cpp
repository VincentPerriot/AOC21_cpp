#include <iostream>
#include <string>
#include <vector>

#include "../../utils/io.h"

int main(int argc, char** argv)
{
  std::vector<std::string> lines = aoc::ReadLines(argv[1]);
  std::vector<int> depths = aoc::ParseIntegers(lines);
  int count = 0;
  for (auto iter = depths.begin() + 1; iter != depths.end(); iter++) {
    if (*iter > *(iter - 1)) count++;
  }
  std::cout << count << "\n";
  return 0;
}