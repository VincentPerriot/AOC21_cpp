#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../../utils/io.h"

class BingoBoard {

public:
    explicit BingoBoard(std::vector<std::vector<int>> numbers, std::vector<std::vector<bool>> checked)
    {
        numbers_ = numbers;
        checked_ = checked;
    };

    bool HasWon() const {
        for (int row = 0; row < 5; row++)
        {
            if (WinningRow(row)) return true;
        }
        for (int col = 0; col < 5; col++)
        {
            if (WinningCol(col)) return true;
        }
        return false;
    }

    void CheckNum(const int number)
    {
        for (int row = 0; row < 5; row++)
        {
            for (int col = 0; col < 5; col++)
            {
                if (number == numbers_[row][col])
                {
                    checked_[row][col] = true;
                }
            }
        }
    }

    int Score(const int called_number) const
    {
        int unchecked_sum = 0;
        for (int row = 0; row < 5; row++)
            for (int col = 0; col < 5; col++)
                if (!checked_[row][col])
                    unchecked_sum += numbers_[row][col];
        
        return unchecked_sum * called_number;
    }

private:
    bool WinningRow(int row) const
    {
        return std::count(checked_[row].begin(), checked_[row].end(), true) == 5;
    };

    bool WinningCol(int col) const
    {
        for (int row = 0; row < 5; row++)
        {
            if (!checked_[row][col]) return false;
        }
        return true;
    };

public:
    std::vector<std::vector<int>> numbers_;
    std::vector<std::vector<bool>> checked_;
};

int main(int argc, char** argv)
{
    // Load comma separated string and put in tokens
    std::vector<std::string> tokenLines = aoc::ReadCommaDelimitedFile(argv[1]);
    std::vector<int> tokens = aoc::ParseIntegers(tokenLines);

    // Load whole file then get rid of comma separated
    std::vector<std::string> lines = aoc::ReadLines(argv[1]); 
    auto it = std::find(lines.begin() + 1, lines.end(), "");
    std::vector<std::string> gridsStr(it + 1, lines.end());

    //build grids, every 5 lines, push all in 5x5 vec<vec<int>>
    std::vector<BingoBoard> grids;

    for(auto iter = gridsStr.begin(); iter < gridsStr.end() - 5; iter += 5)
    {        
        // Skip the blank line 
        if (*iter == "") iter++;

        std::vector<std::vector<int>> numGrid(5, std::vector<int>(5));
        std::vector<std::vector<bool>> boolGrid(5, std::vector<bool>(5));


        for (int row = 0; row < 5; row++)
            {
                int col = 0;
                for (int number : aoc::ParseWhiteSpace(*(iter + row))) 
                {
                    numGrid[row][col] = number;
                    boolGrid[row][col] = false;
                    col++;
                }
            }
        BingoBoard bBoard(numGrid, boolGrid);
        grids.push_back(bBoard);
    }

    for (auto number : tokens)
    {
        for (BingoBoard& bBoard : grids)
        {
            bBoard.CheckNum(number);
            if (bBoard.HasWon())
            {
                std::cout << bBoard.Score(number) << std::endl;
                return 0;
            }
        }
    }

    return 0;
}