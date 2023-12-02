#include <iostream>
#include <bit>
#include <array>
#include <cstdint>
#include <unordered_map>

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

		bool operator ==(const Signal& other) const
		{
			return segments == other.segments;	
		}

		bool operator !=(const Signal& other) const
		{
			return segments != other.segments;	
		}

		Signal operator +(const Signal& other) const
		{
			Signal res(*this);
			res.segments |= other.segments;
			return res;
		}

		Signal operator -(const Signal& other) const 
		{
			Signal res(*this);
			res.segments &= ~other.segments;
			return res;

		}

		bool contains(const Signal& other) const 
		{
			return (segments & other.segments) == other.segments;
		}

		uint8_t getSegments() const {
			return segments;
		}

	private:
		uint8_t segments = 0;
	};

	struct SigHash {
		std::size_t operator()(const Signal& signal) const
		{
			return std::hash<size_t>{}(signal.getSegments());
		}
	};

	struct SigEqual {
		bool operator()(const Signal& a, const Signal& b) const
		{
			return a == b;
		}
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

		int solve() const 
		{
			Signal sig_1, sig_4, sig_7, sig_8;
			for (const Signal& pattern : all_patterns)
			{
				switch (pattern.ActiveSegment())
				{
					case 2:
						sig_1 = pattern;
						std::cout << "found 1" << "\n";
						break;
					case 3:
						sig_7 = pattern;
						std::cout << "found 7" << "\n";
						break;
					case 4:
						sig_4 = pattern;
						std::cout << "found 4" << "\n";
						break;
					case 7:
						sig_8 = pattern;
						std::cout << "found 8" << "\n";
						break;
					default:
						break;
				}
			}
			Signal sig_a = sig_7 - sig_4;
			Signal sig_bd = sig_4 - sig_1;
			Signal sig_abd = sig_a + sig_bd;
			Signal sig_abcdf = sig_abd + sig_1;

			Signal sig_9;
			for (const Signal& pattern : all_patterns)
			{
				if (pattern.contains(sig_abcdf) && pattern != sig_8 ) 
				{
					sig_9 = pattern;
						std::cout << "found 9" << "\n";
					break;
				}
			}
			Signal sig_e = sig_8 - sig_9;
			Signal sig_6, sig_0;
			for (const Signal& pattern : all_patterns)
			{
				if (pattern != sig_9 && pattern.ActiveSegment() == 6)
				{
					if (pattern.contains(sig_1))
					{
						sig_0 = pattern;
						std::cout << "found 0" << "\n";
					} 
					else
					{
						sig_6 = pattern;
						std::cout << "found 6" << "\n";
					}
				}
			}

			Signal sig_c = sig_8 - sig_6;
			Signal sig_d = sig_8 - sig_0;
			Signal sig_f = sig_1 - sig_c;

			Signal sig_2, sig_3, sig_5;

			for (const Signal& pattern : all_patterns)
			{
				if (pattern.ActiveSegment() == 5)
				{
					if (pattern.contains(sig_1))
					{
						sig_3 = pattern;
						std::cout << "found 3" << "\n";
					} else if (pattern.contains(sig_c)) 
					{
						sig_2 = pattern;
						std::cout << "found 2" << "\n";
					} else
					{
                        std::cout << "found 5" << "\n";
						sig_5 = pattern;
					}
				}	
			}

			std::unordered_map<Signal, int, SigHash, SigEqual> umap;
			umap[sig_0] = 0;
			umap[sig_1] = 1;
			umap[sig_2] = 2;
			umap[sig_3] = 3;
			umap[sig_4] = 4;
			umap[sig_5] = 5;
			umap[sig_6] = 6;
			umap[sig_7] = 7;
			umap[sig_8] = 8;
			umap[sig_9] = 9;

			int final_res = 0;
			
			for(const Signal& output_sig : outputs)
			{
				const auto val = umap.find(output_sig);
				if (val == umap.end())
					throw std::out_of_range("Key not found");
				std::cout << "adding " << val->second << "\n";
				final_res = final_res * 10 + val->second;
			}

			return final_res;
		}

	private:
		std::array<Signal, 10> all_patterns;
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

	int total_outputs = 0;

	for (const auto& display : displays)
	{
		total_outputs += display.solve();
	}

	std::cout << total_outputs << std::endl;

	return 0;
}