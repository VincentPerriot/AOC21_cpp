#include <iostream>
#include <string>
#include <vector>

#include "../../utils/io.h"

struct Move {
  std::string direction;
  int dist;
};

int main(int argc, char** argv)
{
  std::vector<std::string> lines = aoc::ReadLines(argv[1]);  

  std::vector<Move> moves;
  char delimiter = ' ';
  for (std::string line : lines)
  {
    Move move;

    int pos = line.find(delimiter);
    move.direction = line.substr(0, pos);
    std::string distString = line.substr(pos + 1);
    move.dist = std::stoi(distString);

    moves.push_back(move);
  }

  // Get position
  int depth = 0;
  int forward = 0;
  int aim = 0;

  for (Move move : moves)
  {
    if (move.direction == "up")
      aim -= move.dist;
    else if (move.direction == "down")
      aim += move.dist;
    else if (move.direction == "forward")
    {
      forward += move.dist;
      depth += move.dist * aim;
    }
    else 
      exit(EXIT_FAILURE);
  }

  int res = depth * forward;
  std::cout << res << std::endl;

  return 0;
}