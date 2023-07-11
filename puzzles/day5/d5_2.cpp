#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <iterator>

#include "../../utils/io.h"

class Grid {
public:
    explicit Grid(const int max_x, const int max_y)
        : rep_(max_x + 1, std::vector<int>(max_y + 1, 0)) {}
    
    auto begin() { return rep_.begin(); }
    auto end()   { return rep_.end(); } 

private:
    std::vector<std::vector<int>> rep_;
    friend class Line;
};

class Line{
public:
    explicit Line(std::string s) {
        std::regex pattern(R"((\d+),(\d+)\s->\s(\d+),(\d+))");

        // match iterator only need to pass it with s and pattern to search func
        std::smatch m;
        if(std::regex_search(s, m, pattern))
        {
            x1 = std::stoi(m[1]);
            y1 = std::stoi(m[2]);
            x2 = std::stoi(m[3]);
            y2 = std::stoi(m[4]);
        }
    }

    int MaxX() const 
    {
        return std::max(x1, x2);
    }

    int MaxY() const 
    {
        return std::max(y1, y2);
    }

    void MarkOnGrid(Grid& grid) const 
    {
        if (x1 == x2)
        {
            // Mark grid from y0 to y1
            const int min_y = std::min(y1, y2);
            const int max_y = std::max(y1, y2);
            for(int y = min_y; y <= max_y; y++)
            {
                grid.rep_[x1][y]++;
            }
            return;
        }
        if (y1 == y2)
        {
            // Mark grid from y0 to y1
            const int min_x = std::min(x1, x2);
            const int max_x = std::max(x1, x2);
            for(int x = min_x; x <= max_x; x++)
            {
                grid.rep_[x][y1]++;
            }
            return;
        }
        // If not right or up we just reverse start x or y
        const int min_x = std::min(x1, x2);
        const int max_x = std::max(x1, x2);

        bool right = min_x == x1;
        int startY = right ? y1 : y2;
        int endY = right ? y2 : y1;

        bool up = startY < endY;

        for (int i = 0; i <= (max_x - min_x); i++)
        {
          int x = min_x + i; 
          int y = up ? (startY + i) : (startY - i);
          grid.rep_[x][y]++;
        }
    }

public:
    int x1 = 0;
    int x2 = 0; 
    int y1 = 0; 
    int y2 = 0; 
};

int main(int argc, char** argv)
{
    std::vector<std::string> strLines = aoc::ReadLines(argv[1]);
    std::vector<Line> lines;

    int max_x = 0;
    int max_y = 0;
    for (auto strLine : strLines)
    {
        lines.emplace_back(strLine);
        max_x = std::max(max_x, lines.back().MaxX());
        max_y = std::max(max_y, lines.back().MaxY());
    }

    Grid grid(max_x, max_y);
    for (auto line : lines)
    {
        line.MarkOnGrid(grid);
    }

    int count = 0;
    for (auto& vecPoints : grid)
        for (auto& point : vecPoints)
            if (point >= 2)
                count++;

    std::cout << "Parsed " << lines.size() << " lines\n";
    std::cout << "Grid size " << max_x << " x " << max_y << "\n"; 
    std::cout << "count is : " << count << "\n";

    return 0;
}