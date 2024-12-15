#include <iostream>
#include <string>
#include <vector>
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
  
  Vector2 operator-(const Vector2& other) const
  {
    return Vector2(this->x - other.x, this->y - other.y);
  }
};

enum Direction
{
  LEFT, UP, RIGHT, DOWN
};

std::vector<std::string> getFileLines(const std::string& filename);

int main() 
{
  std::string filename = "input.txt";
  std::vector<std::string> fileLines = getFileLines(filename);

  if (fileLines.size() == 0)
  {
    std::cout << "FAILED TO FIND INPUT DATA!\n";
    return -1;
  }

  // Given a map showing position of robot, boxes, and moves that the robot takes
  // If a move hits into a wall or a box that hits into a wall no movement happens
  // Run through all the steps and calculate GPS of each box
  // GPS = 100 * (DISTANCE_FROM_TOP) + DISTANCE_FROM_LEFT

  // Need position for robot
  // Need positions for boxes
  // Need positions for walls -- not necessarily just at the edges!

  Vector2 robotPosition;
  std::vector<Direction> directions;

  for (int i = 0; i < fileLines.size(); i++)
  {
    std::string currentLine = fileLines[i];

    for (int j = 0; j < currentLine.length(); j++)
    {
       char c = currentLine[j];
       Vector2 currentPos(j, i);

       if (c == '@')
       {
         robotPosition = currentPos;
       }
       else if (c == '<')
       {
         directions.push_back(Direction::LEFT);
       }
       else if (c == 'v')
       {
         directions.push_back(Direction::DOWN);
       }
       else if (c == '^')
       {
         directions.push_back(Direction::UP);
       }
       else if (c == '>')
       {
         directions.push_back(Direction::RIGHT);
       }
    }
  }

  // TRAVERSE BASED ON MOVEMENTS!

  int maxX = fileLines[0].length() - 1;
  int maxY = fileLines.size() - 1;

  for (int i = 0; i < directions.size(); i++)
  {
    Direction direction = directions[i];
    Vector2 movement;

    switch (direction)
    {
      case Direction::LEFT:
        movement = Vector2(-1, 0);
	std::cout << "ATTEMPTING TO MOVE LEFT\n";
	break;
      case Direction::UP:
        movement = Vector2(0, -1);
	std::cout << "ATTEMPTING TO MOVE UP\n";
	break;
      case Direction::DOWN:
        movement = Vector2(0, 1);
	std::cout << "ATTEMPTING TO MOVE DOWN\n";
	break;
      case Direction::RIGHT:
        movement = Vector2(1, 0);
	std::cout << "ATTEMPTING TO MOVE RIGHT\n";
	break;
    }

    Vector2 newPosition = robotPosition + movement;
    std::cout << "NEW POSITION: " << newPosition.x << " " << newPosition.y << "\n";

    // Are we hitting the edges of the map (outer walls)?
    if (newPosition.x == 0 || newPosition.x == maxX) 
    {
      std::cout << "HIT OUTER VERTICAL WALL DIRECTLY\n";
      continue;
    }
    if (newPosition.y == 0 || newPosition.y == maxY)
    {
      std::cout << "HIT OUTER HORIZONTAL WALL DIRECTLY\n";
      continue;
    }

    // Are we colliding with the wall directly?
    // Just use the map itself for walls?
    if (fileLines[newPosition.y][newPosition.x] == '#')
    {
      std::cout << "HIT AN INNER WALL DIRECTLY\n";
      continue;
    }

    // Just manipulate the text?
    char nextTile = fileLines[newPosition.y][newPosition.x];

    if (nextTile == '.')
    {
      // Just move the robot
      std::cout << "MOVING TO FREE SPACE\n";
      fileLines[robotPosition.y][robotPosition.x] = '.';
      fileLines[newPosition.y][newPosition.x] = '@';
      robotPosition = newPosition;
    }
    else
    {
      // We have hit a box!
      // Can it scoot?
      // Walk until we hit a free space
      std::cout << "HIT A BOX!\n";

      Vector2 nextPosition = newPosition + movement;
      int boxCount = 1;
      bool canScoot = false;

      while ((nextPosition.x > 0 && nextPosition.x < maxX) && (nextPosition.y > 0 && nextPosition.y < maxY))
      {
        char next = fileLines[nextPosition.y][nextPosition.x];

	if (next == '.')
	{
	  std::cout << "BOX CAN SCOOT!\n";
	  canScoot = true;
	  break;
	}

	if (next == '#')
	{
	  std::cout << "BOX(S) WILL HIT WALL\n";
	  canScoot = false;
	  break;
	}

	nextPosition = nextPosition + movement;
	boxCount++;
      }
      
      if (!canScoot)
      {
        std::cout << "BOXES CANNOT MOVE!\n";
      }
      else
      {
        // Scoot however many boxes we found
	std::cout << "SCOOTING: " << boxCount << " BOXES\n";
        for (int j = 1; j <=  boxCount; j++)
	{
	  Vector2 delta;
	  delta.x = movement.x * j;
	  delta.y = movement.y * j;

	  Vector2 newBoxPos = newPosition + delta;

	  std::cout << "NEW BOX POS: " << newBoxPos.x << " " << newBoxPos.y << "\n";

	  fileLines[newBoxPos.y][newBoxPos.x] = 'O';
	}

	// Setup new position
	fileLines[robotPosition.y][robotPosition.x] = '.';
	fileLines[newPosition.y][newPosition.x] = '@';
	robotPosition = newPosition;
      }
    }
  }

   std::cout << "MAP AFTER STUFF:\n";

   long gpsSum = 0;

   for (int i = 0; i < fileLines.size(); i++)
   {
     std::cout << fileLines[i] << "\n";

     for (int j = 0; j < fileLines[i].length(); j++)
     {
       if (fileLines[i][j] == 'O')
       {
         // GPS = 100 * DY + DX
	 long gps = (100 * i) + j;

	 gpsSum = gpsSum + gps;
       }
     }
   }

   std::cout << "GPS SUM: " << gpsSum << "\n";

     


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

  while (std::getline(file, currentLine))
  {
    std::cout << currentLine << "\n";
    results.push_back(currentLine);
  }

  return results;
}
