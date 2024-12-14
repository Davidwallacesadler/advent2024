#include <iostream>
#include <vector>

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

  Entity(Vector2 pos, Vector2 vel): position(pos), velocity(vel) {}
};

int main()
{
  // Given a list of positions and velocities -- simulate steps
  // When hitting a wall we just warp --  new Position = velocity applied mod maxX, mod maxY
  // Need to simulate 100 steps
  // Positions can overlap
  // maxX = 101, maxY = 103
  // Split into quadrants - discarding middle positions
  // Count number of positions in each quadrant and multiply

  int maxX = 11; //101;
  int maxY = 7; //103;

  std::vector<Entity> entities;

  // Test to match example
  entities.push_back(Entity(Vector2(2, 4), Vector2(2, -3)));

  int maxStepCount = 5;

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
      else if (newPosition.x > maxX)
      {
        newPosition.x = newPosition.x % maxX;
      }
      
      if (newPosition.y < 0)
      {
        newPosition.y = maxY + newPosition.y;
      }
      else if (newPosition.y > maxY)
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

  int midX = (maxX - 1) / 2;
  int midY = (maxY - 1) / 2;

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


}
