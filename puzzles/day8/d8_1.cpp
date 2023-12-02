#include <iostream>
#include <bit>
#include <array>
#include <cstdint>

#include "../../utils/io.h"

namespace {

	class Signal {
	public:
		Signal() = default;

		explicit Signal(std::string str)
		{
			for (const char& c : str)
			{
				const int offset = c - 'a';
				segments |= (1 << offset);
			}
		}

		int ActiveSegment() const
		{
			return std::popcount(segments);
		}

	private:
		uint8_t segments = 0;
	};

	class Display {
	public:
		explicit Display(const std::string& rep)
		{
			std::vector<std::string> parts = aoc::strToVecStr(rep);
			for (int pattern_i = 0; pattern_i < 10; pattern_i++)
			{
				all_patterns[pattern_i] = Signal(parts[pattern_i]);
			}
			// part 10 is ignored
			for (int output_i = 0; output_i < 4; output_i++)
			{
				outputs[output_i] = Signal(parts[11+output_i]);
			}
		}

		int UniqueDigitsOutput() const
		{
			int count = 0;
			for (const Signal& signal : outputs)
			{
				switch (signal.ActiveSegment())
				{
					case 2:
					case 3:
					case 4:
					case 7:
						count++;
						break;
					default:
						break;
				}
			}
			return count;
		}

	private:
		std::array<Signal, 7> all_patterns;
		std::array<Signal, 4> outputs;
	};

};

int main()
{
	std::vector<std::string> lines = aoc::ReadLines("../puzzles/day8/input.txt");
	std::vector<Display> displays;

	for (const auto& line : lines)
	{
		displays.emplace_back(line);
	} 

	int total_unique = 0;

	for (const auto& display : displays)
	{
		total_unique += display.UniqueDigitsOutput();
	}

	std::cout << total_unique << std::endl;

	return 0;
}