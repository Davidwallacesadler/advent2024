#include<iostream>
#include<fstream>
#include<string>
#include<vector>

struct Position
{
  int x, y;

  Position() : x(0), y(0) {}
  Position(int nx, int ny) : x(nx), y(ny) {}

  bool operator==(const Position& other) const
  {
    return this->x == other.x && this->y == other.y;
  }

  Position operator-(const Position& other) const
  {
    return Position(this->x - other.x, this->y - other.y);
  }

  Position operator+(const Position& other) const
  {
    return Position(this->x + other.x, this->y + other.y);
  }
};

struct Node
{
  Position pos;
  bool hasBeenVisited;

  Node() : pos(), hasBeenVisited(false) {}
  Node(Position p) : pos(p), hasBeenVisited(false) {}
};

std::vector<std::string> getFileLines(const std::string& filename);

int main()
{
  std::vector<std::string> fileLines = getFileLines("testInput.txt");

  if (fileLines.size() == 0)
  {
    std::cout << "NO INPUT DATA FOUND!\n";
    return EXIT_FAILURE;
  }

  std::vector<Position> startPositions;
  std::vector<Node> nodes;
  int columnCount = fileLines[0].size();

  for (int i = 0; i < fileLines.size(); i++)
  {
    for (int j = 0; j < fileLines[i].length(); j++)
    {
      int heightValue = fileLines[i][j] - '0';
      Position currentPosition(j, i);

      nodes.push_back(Node(currentPosition));
      if (heightValue == 0)
      {
        startPositions.push_back(currentPosition);
      }
    }

    std::cout << fileLines[i] << "\n";
  }

  // Hiking trail = any path from 0 to 9 (always increasing)
  // Trailhead = the start position of any hiking trail
  // Score = the number of 9's reachable from a trailhead

  // Prob gotta do depth first search or something...

  for (Position start : startPositions)
  {
    std::cout << "Starting out from: " << start.x << " , " << start.y << "\n";

    Position left = start - Position(1, 0);
    Position up = start + Position(0, 1);
    Position right = start + Position(1, 0);
    Position down = start + Position(0, 1);


  }


  return EXIT_SUCCESS;
}

std::vector<std::string> getFileLines(const std::string& filename)
{
  std::ifstream file(filename);
  std::vector<std::string> results;

  if (!file)
  {
    std::cout << "FAILED TO OPEN FILE: " << filename << "\n";
    return results;
  }

  std::string currentLine;
  while(std::getline(file, currentLine))
  {
    results.push_back(currentLine);
  }

  return results;
}
