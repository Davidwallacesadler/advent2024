#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

struct Position
{
  int x, y;

  Position(): x(0), y(0) {}
  Position(int nx, int ny): x(nx), y(ny) {}

  bool operator==(const Position& other) const
  {
    return this->x == other.x && this->y == other.y;
  }
};

struct Region
{
  std::vector<Position> positions;

  Region(): positions() {}

  bool isContiguousWith(const Position& otherPos) const
  {
    // Its either inside or touching the edge
    // For all positions there is at least one that touches a side with the other

    for (int i = 0; i < positions.size(); i++)
    {
      Position currentPos = positions[i];
      
      // Check left
      if (currentPos.x == otherPos.x + 1 && currentPos.y == otherPos.y)
      {
        return true;
      }

      // Check up
      if (currentPos.y == otherPos.y + 1 && currentPos.x == otherPos.x)
      {
        return true;
      }

      // Check right
      if (currentPos.x == otherPos.x - 1 && currentPos.y == otherPos.y)
      {
        return true;
      }
      
      // Check down
      if (currentPos.y == otherPos.y - 1 && currentPos.x == otherPos.x)
      {
        return true;
      }

      // Check same
      if (currentPos == otherPos)
      {
        return true;
      }
    }

    return false;
  }
};

enum Direction
{
  LEFT, UP, RIGHT, DOWN
};

std::vector<std::string> getFileLines(const std::string& filename);

int main()
{
  std::vector<std::string> fileLines = getFileLines("testInput.txt");

  for (int i = 0; i < fileLines.size(); i++)
  {
    std::cout << fileLines[i] << "\n";
  }

  // Calculate cost of fence
  // Each character is a plant
  // Contiguous Groups of the same plants form regions
  // Fencing cost for regions is determined by area and perimeter
  // Area - # of plants in the region
  // Perimeter - # of sides of the region
  // Price of a region = Area * Perimeter

  // NOTE: REGIONS MUST BE CONTIGUOUS
  
  // Iterate over the board -- use a map from char to positions (Defines regions)
  // Calculate area: map[char].size()
  // Calculate perimeter: get the positions and iterate checking for adjacent blocks

  std::map<char, std::vector<Position> > charToRegion;

  for (int i = 0; i < fileLines.size(); i++)
  {
    for (int j = 0; j < fileLines[i].length(); j++)
    {
      char currentChar = fileLines[i][j];
      Position newPos(j, i);

      if (charToRegion.count(currentChar) == 1)
      {
        charToRegion[currentChar].push_back(newPos);
      }
      else
      {
        std::vector<Position> newRegion;
	newRegion.push_back(newPos);

        charToRegion[currentChar] = newRegion;
      }
    }
  }

  int totalCost = 0;

  for (std::map<char, std::vector<Position> >::iterator iter = charToRegion.begin(); iter != charToRegion.end(); iter++)
  {
    char plant = iter->first;
    std::vector<Position> region = iter->second;

    std::cout << "CALCULATING PERIMETER FOR PLANT: " << plant << "\n";

    // TODO: Need to break up region into sub-regions based on any that are "islands" -- each region must be contiguous
    std::vector<Region> contiguousRegions;

    for (int i = 0; i < region.size(); i++)
    {
      Position currentPos = region[i];
      bool hasBeenAdded = false;

      // Find a region in which this pos is contiguous or start a new region

      for (int j = 0; j < contiguousRegions.size(); j++)
      {
        Region currentRegion = contiguousRegions[j];

	if (currentRegion.isContiguousWith(currentPos))
	{
	  contiguousRegions[j].positions.push_back(currentPos);
	  hasBeenAdded = true;
	  break;
	}
      }

      if (!hasBeenAdded)
      {

        std::cout << "STARTING NEW SUBREGION\n";
        Region newRegion;
	newRegion.positions.push_back(currentPos);

	contiguousRegions.push_back(newRegion);
      }
    }

    std::cout << "SUBREGIONS FOUND: " << contiguousRegions.size() << "\n";

    int totalPerimeter = 0;
    
    for (int i = 0; i < region.size(); i++)
    {
      Position currentPos = region[i];

      std::vector<bool> openSides;
      openSides.push_back(true);
      openSides.push_back(true);
      openSides.push_back(true);
      openSides.push_back(true);

      for (int j = 0; j < region.size(); j++)
      {
        if (j == i)
	{
	  continue;
	}

	Position otherPos = region[j];

	// Check left
	if (otherPos.x == currentPos.x - 1 && otherPos.y == currentPos.y)
	{
	  openSides[Direction::LEFT] = false;
	  continue;
	}

	// Check up
	if (otherPos.y == currentPos.y + 1 && otherPos.x == currentPos.x)
	{
	  openSides[Direction::UP] = false;
	  continue;
	}

	// Check right
	if (otherPos.x == currentPos.x + 1 && otherPos.y == currentPos.y)
	{
	  openSides[Direction::RIGHT] = false;
	  continue;
	}

	// Check down
	if (otherPos.y == currentPos.y -1 && otherPos.x == currentPos.x)
	{
	  openSides[Direction::DOWN] = false;
	}
      }

      std::cout << "OPEN SIDES:\n";
      int openSideCount = 0;
      for (int j = 0; j < openSides.size(); j++)
      {
        if (openSides[j])
        {
          std::cout << static_cast<Direction>(j) << "\n";
	  openSideCount++;
        }
      }

      totalPerimeter = totalPerimeter + openSideCount;
    }

    std::cout << "TOTAL PERIMETER: " << totalPerimeter << "\n";
    std::cout << "TOTAL AREA: " << region.size() << "\n";

    int regionCost = totalPerimeter * region.size();

    std::cout << "COST: " << regionCost << "\n";

    totalCost = totalCost + regionCost;
  }

  std::cout << "TOTAL COST: " << totalCost << "\n";

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
