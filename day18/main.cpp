#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

struct Vector2
{
  int x, y;

	Vector2(): x(0), y(0) {}
	Vector2(int nx, int ny): x(nx), y(ny) {}

	bool operator==(const Vector2& other) const
	{
	  return this->x == other.x && this->y == other.y;
	}
};

bool vectorContainsVec2(const std::vector<Vector2>& list, const Vector2& vector);

int main()
{
  // Read from file
	std::ifstream file("testInput.txt");

	if (!file)
	{
	  std::cout << "NO INPUT FOUND!\n";
		return -1;
	}
	
	// Setup memory scenario
	Vector2 memoryMaxSize(6, 6);
	std::vector<Vector2> corruptPositions;

	while (!file.eof())
	{
	  std::string currentLine;
		std::string buildString;
		Vector2 bytePosition;

		file >> currentLine;

		for (int i = 0; i < currentLine.length(); i++)
		{
		  if (currentLine[i] == ',')
			{
			  // X = distance from the left edge
			  bytePosition.x = stoi(buildString);
				buildString = "";
			} 
			else
			{
			  buildString = buildString + currentLine[i];
			}
		}

		if (buildString.length() > 0)
		{
		  bytePosition.y = stoi(buildString);
		}
		corruptPositions.emplace_back(bytePosition);
	}

	for (int i = 0; i < corruptPositions.size(); i++)
	{
	  std::cout << "# " << corruptPositions[i].x << " " << corruptPositions[i].y << "\n";
	}

	for (int i = 0; i < memoryMaxSize.x; i++)
	{
	  for (int j = 0; j < memoryMaxSize.y; j++)
		{
		  Vector2 pos(j, i);
			if (vectorContainsVec2(corruptPositions, pos))
			{
			  std::cout << "#";
			}
			else
			{
			  std::cout << ".";
			}
		}
		std::cout << "\n";
	}

  // We are trying to get from 0,0 to max.x max.y	

}

bool vectorContainsVec2(const std::vector<Vector2>& list, const Vector2& vector)
{
  bool isContained = false;
	for (int i = 0; i < list.size(); i++)
	{
	  if (list[i] == vector)
		{
		  isContained = true;
			break;
		}
	}

	return isContained;
}
