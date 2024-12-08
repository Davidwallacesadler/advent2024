#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

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

std::vector<std::string> getFileLines(const std::string& filename);

int main()
{
  std::vector<std::string> fileLines = getFileLines("input.txt");
  std::map<char, std::vector<Position> > antaneaToPositions;

  for (int i = 0; i < fileLines.size(); i++)
  {
    std::cout << fileLines[i] << "\n";
    for (int j = 0; j < fileLines[i].length(); j++)
    {
      char currentChar = fileLines[i][j];
      Position currentPosition(j, i);
      if (currentChar != '.')
      {
        // This is an antanea
        if (antaneaToPositions.count(currentChar) == 1)
        {
          antaneaToPositions[currentChar].push_back(currentPosition);
        }
        else 
        {
          std::vector<Position> newPositions;
          newPositions.push_back(currentPosition);
          antaneaToPositions[currentChar] = newPositions;
        }
      }
    }
  }


  // So we want to look at all antaneas of the same type'
  // For each look at every other and use rise/run to determine where antinode will go based on this

  int maxX = fileLines[0].length();
  int maxY = fileLines.size();


  std::vector<Position> uniquePositions;

  for (std::map<char, std::vector<Position> >::iterator it = antaneaToPositions.begin(); it != antaneaToPositions.end(); it++)
  {
    std::cout << it->first << "\n";

    int currentPositionIndex = 0;
    std::vector<Position> positions = it->second;

    while (currentPositionIndex < positions.size())
    {
      for (int i = 0; i < positions.size(); i++)
      {
        if (i == currentPositionIndex)
	{
	  continue;
	}

	// Get the rise and run
	Position delta = positions[i] - positions[currentPositionIndex];

	std::cout << "RISE: " << delta.y << " RUN: " << delta.x << "\n";

	// Apply rise and run to i and see if its in the bounds
	Position posA = positions[i] + delta;
	Position posB = positions[currentPositionIndex] - delta;

	std::cout << "ANTINODE A AT: " << posA.x << " , " << posA.y << "\n";
	std::cout << "ANTINODE B AT: " << posB.x << " , " << posB.y << "\n";

	if (posA.x >= 0 && posA.x < maxX && posA.y >= 0 && posA.y < maxY)
	{
	  // posA is on the board!
	  std::cout << "POS A ON THE BOARD!\n";

	  bool isAdded = false;
	  for (Position pos : uniquePositions)
	  {
	    if (pos == posA)
	    {
	      isAdded = true;
	    }
	  }
	  if (!isAdded)
	  {
	    uniquePositions.push_back(posA);
	  }

	}

	if (posB.x >= 0 && posB.x < maxX && posB.y >= 0 && posB.y < maxY)
	{
	  // posB is on the board!
	  std::cout << "POS B ON THE BOARD!\n";


	  bool isAdded = false;
	  for (Position pos : uniquePositions)
	  {
	    if (pos == posB)
	    {
	      isAdded = true;
	    }
	  }
	  if (!isAdded)
	  {
	    uniquePositions.push_back(posB);
	  }
	}
      }
      currentPositionIndex++;
    }
  }

  std::cout << "UNIQUE POSITIONS: " << uniquePositions.size() << "\n";


  return EXIT_SUCCESS;
}


std::vector<std::string> getFileLines(const std::string& filename)
{
  std::ifstream file(filename);
  std::vector<std::string> results;

  if (!file)
  {
    std::cout << "FAILED TO READ FILE: " << filename << "\n";
    return results;
  }

  std::string currentLine;
  while (std::getline(file, currentLine))
  {
    results.push_back(currentLine);
  }

  return results;
}
