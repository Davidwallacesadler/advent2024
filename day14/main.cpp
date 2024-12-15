#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Vector2
{
  int x, y;

  Vector2(): x(0), y(0) {}
  Vector2(int nx, int ny): x(nx), y(ny) {}

  Vector2 operator+(const Vector2& other) const
  {
    return Vector2(this->x + other.x, this->y + other.y);
  }

  void print() const
  {
    std::cout << "X: " << this->x << " Y: " << this->y << "\n";
  }
};

struct Entity
{
  Vector2 position;
  Vector2 velocity;

  Entity(): position(), velocity() {}
  Entity(Vector2 pos, Vector2 vel): position(pos), velocity(vel) {}

  void print() const
  {
    std::cout << "P: ";
    this->position.print();
    std::cout << "V: ";
    this->velocity.print();
  }
};

std::vector<std::string> getFileLines(const std::string& filename);

int main()
{
  std::string filename = "input.txt";
  std::vector<std::string> fileLines = getFileLines(filename);

  if (fileLines.size() == 0)
  {
    std::cout << "NO INPUT FOUND FOR " << filename << "\n";
    return -1;
  }

  std::vector<Entity> entities;

  for (int i = 0; i < fileLines.size(); i++)
  {
    std::string line = fileLines[i];

    Entity newEntity;
    std::string buildString;
    bool settingUpPos = true;

    for (int j = 2; j < line.length(); j++)
    {
      char c = line[j];

      if (c == ',')
      {
        if (settingUpPos)
	{
          newEntity.position.x = stoi(buildString);
	}
	else
	{
	  newEntity.velocity.x = stoi(buildString);
	}
	buildString = "";
	continue;
      }

      if (c == ' ')
      {
        newEntity.position.y = stoi(buildString);
	settingUpPos = false;

	buildString = "";
	j = j + 2;
	continue;
      }

      buildString = buildString + c;
    }

    newEntity.velocity.y = stoi(buildString);

    newEntity.print();
    std::cout << "\n";

    entities.push_back(newEntity);
  }


  // Given a list of positions and velocities -- simulate steps
  // When hitting a wall we just warp --  new Position = velocity applied mod maxX, mod maxY
  // Need to simulate 100 steps
  // Positions can overlap
  // maxX = 101, maxY = 103
  // Split into quadrants - discarding middle positions
  // Count number of positions in each quadrant and multiply

  int maxX = 101;
  int maxY = 103;

  int midX = (maxX - 1) / 2;
  int midY = (maxY - 1) / 2;

  std::cout << "MAP SIZE: X " << maxX << " Y " << maxY << "\n";
  std::cout << "MID: X " << midX << " Y " << midY << "\n";

  //  std::vector<Entity> entities;

  // Test to match example
  //  entities.push_back(Entity(Vector2(2, 4), Vector2(2, -3)));

  int maxStepCount = 100;

  for (int i = 0; i < maxStepCount; i++)
  {
    // Move each entity based on it velocity
    // Mod each movement by maxX and maxY to simulate "warp"
    // OR if either is negative subtract that value from max

    for (int j = 0; j < entities.size(); j++)
    {
      Entity e = entities[j];

      Vector2 newPosition = e.position + e.velocity;

      // Normalize position
      if (newPosition.x < 0)
      {
        newPosition.x = maxX + newPosition.x;
      } 
      else if (newPosition.x >= maxX)
      {
        newPosition.x = newPosition.x % maxX;
      }
      
      if (newPosition.y < 0)
      {
        newPosition.y = maxY + newPosition.y;
      }
      else if (newPosition.y >= maxY)
      {
        newPosition.y = newPosition.y % maxY;
      }

      std::cout << "ENTITY NOW AT: \n";
      newPosition.print();

      entities[j].position = newPosition;
    }
  }

  // Split positions into quadrants
  int topLhPositions = 0;
  int topRhPositions = 0;
  int botLhPositions = 0;
  int botRhPositions = 0;

  Vector2 midPosition(midX, midY);

  for (int i = 0; i < entities.size(); i++)
  {
    Entity e = entities[i];
    
    if (e.position.x < midPosition.x)
    {
      // Its on the left
      if (e.position.y < midPosition.y)
      {
	botLhPositions++;
      }
      else if (e.position.y > midPosition.y)
      {
        topLhPositions++;
      }
    }
    else if (e.position.x > midPosition.x)
    {
      // Its on the right
      if (e.position.y < midPosition.y)
      {
        botRhPositions++;
      }
      else if (e.position.y > midPosition.y)
      {
        topRhPositions++;
      }
    }
  }

  std::cout << "TOP LH: " << topLhPositions << "\n";
  std::cout << "TOP RH: " << topRhPositions << "\n";
  std::cout << "BOT LH: " << botLhPositions << "\n";
  std::cout << "BOT RH: " << botRhPositions << "\n";

  long safetyScore = topLhPositions * topRhPositions * botLhPositions * botRhPositions;

  std::cout << "SAFEFY SCORE: " << safetyScore << "\n";
}

std::vector<std::string> getFileLines(const std::string& filename)
{
  std::ifstream file(filename);
  std::vector<std::string> results;

  if (!file)
  {
    return results;
  }

  std::string currentLine;
  while(std::getline(file, currentLine))
  {
    std::cout << currentLine << "\n";
    results.push_back(currentLine);
  }
  
  return results;
}
