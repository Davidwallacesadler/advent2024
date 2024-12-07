#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Position
{
  int x, y = 0;

  Position() : x(0), y(0) {}
  Position(int newX, int newY) : x(newX), y(newY) {}

  bool operator==(const Position& other) const
  {
    return this->x == other.x && this->y == other.y;
  }
};

enum Direction
{
  UP, RIGHT, DOWN, LEFT
};

class Guard
{
  Direction mFaceDirection = Direction::UP;
  Position mPosition;
 public:
  void turnRight();
  void stepForward(); 
  void setPosition(Position newPos);

  Direction getFaceDirection() const;
  Position getPosition() const;
};

void Guard::turnRight()
{
  mFaceDirection = static_cast<Direction>((mFaceDirection + 1) % 4);
}

void Guard::stepForward()
{
  switch (mFaceDirection)
  {
    case UP:
      mPosition.y--;
      break;

    case DOWN:
      mPosition.y++;
      break;
    
    case RIGHT:
      mPosition.x++;
      break;

    case LEFT:
      mPosition.x--;
  }
}

void Guard::setPosition(Position newPos)
{
  mPosition = newPos;
}

Direction Guard::getFaceDirection() const
{
  return mFaceDirection;
}

Position Guard::getPosition() const
{
  return mPosition;
}

std::vector<std::string> getFileLines(const std::string& filename);
bool guardIsExitingMap(const std::vector<std::string>& fileLines, const Guard& guard);

int main()
{
  std::vector<std::string> fileLines = getFileLines("input.txt");

  if (fileLines.size() == 0)
  {
    std::cout << "NO INPUT DATA FOUND!\n";
    return EXIT_FAILURE;
  }

  std::cout << "FILE CONTENTS: \n";
  for (int i = 0; i < fileLines.size(); i++)
  {
    std::cout << fileLines[i] << "\n";
  }

  Guard guard;
  std::vector<Position> uniquePositions;
  std::vector<Position> lastObsticlePositions;
  int obsticlesSeen = 0;
  int intersectionCount = 0;

  // Setup the guard
  bool foundGuard = false;
  for (int i = 0; i < fileLines.size(); i++)
  {
    if (foundGuard)
    {
      break;
    }
    for (int j = 0; j < fileLines[i].length(); j++)
    {
      if (fileLines[i][j] == '^')
      {
        Position guardStartPos(j, i);
        guard.setPosition(guardStartPos);
      	foundGuard = true;
      	fileLines[i][j] = '.';
      	break;
      }
    }
  }

  // Walk the guard while not at the edge and looking off of it
  while (!guardIsExitingMap(fileLines, guard))
  {
    Position guardPosition = guard.getPosition();
    Direction guardDirection = guard.getFaceDirection();

    int i = guardPosition.y;
    int j = guardPosition.x;
    
    std::cout << "GUARD POSITION: i " << i << " , j: " << j << "\n"; 

    // Update visited locations
    bool shouldAddPosition = true;
    for (int i = 0; i < uniquePositions.size(); i++)
    {
      Position pos = uniquePositions[i];
      if (pos == guardPosition)
      {
        shouldAddPosition = false;
        break;
      }
    }
    if (shouldAddPosition)
    {
      uniquePositions.push_back(guardPosition);
    }

    int nextI, nextJ;
    switch (guardDirection)
    {
      case UP:
        nextI = i - 1;
      	nextJ = j;
      	break;
      
      case DOWN:
        nextI = i + 1;
      	nextJ = j;
      	break;

      case LEFT:
        nextI = i;
      	nextJ = j - 1;
      	break;
        
      case RIGHT:
        nextI = i;
      	nextJ = j + 1;
    }

    char nextTile = fileLines[nextI][nextJ];

    std::cout << "NEXT POSITION: i " << nextI << " , j: " << nextJ << ". Char: " << nextTile << "\n"; 

    // Check last obsticles for loop point
    // Who am I passing on the right?
    // If its a third obisticle and I am passing it on the LEFT this is a point
    for (Position obsticlePosition : lastObsticlePositions)
    {
      switch (guardDirection)
      {
        case LEFT:
          if (nextJ == obsticlePosition.x && nextI > obsticlePosition.y)
          {
            intersectionCount++;
          }
          break;
        case RIGHT:
          if (nextJ == obsticlePosition.x && nextI < obsticlePosition.y)
          {
            intersectionCount++;
          }
          break;
        case UP:
          if (nextI == obsticlePosition.y && nextJ < obsticlePosition.x)
          {
            intersectionCount++;
          }
          break;
        case DOWN:
          if (nextI == obsticlePosition.y && nextJ > obsticlePosition.x)
          {
            intersectionCount++;
          }
      }
    }

    if (nextTile == '.')
    {
      std::cout << "Stepping Forward!!\n";
      guard.stepForward();
    }
    else
    {
      std::cout << "HIT OBSTICLE: Turning right!!\n";

      if (obsticlesSeen % 3 == 0)
      {
        Position obsticlePosition(nextJ, nextI);
        lastObsticlePositions.push_back(obsticlePosition);
      }

      obsticlesSeen++;

      guard.turnRight();
    }
  }

  std::cout << "UNIQUE POSITIONS: " << uniquePositions.size() << "\n";
  std::cout << "INTERSECTION COUNT: " << intersectionCount << "\n";

  return EXIT_SUCCESS;
}

bool guardIsExitingMap(const std::vector<std::string>& fileLines, const Guard& guard)
{
  int maxX = fileLines[0].length() - 1;
  int maxY = fileLines.size() - 1;

  Position guardPosition = guard.getPosition();
  Direction guardDirection = guard.getFaceDirection();

  bool isExitingTop = guardPosition.y == 0 && guardDirection == Direction::UP;
  bool isExitingRight = guardPosition.x == maxX && guardDirection == Direction::RIGHT;
  bool isExitingBottom = guardPosition.y == maxY && guardDirection == Direction::DOWN;
  bool isExitingLeft = guardPosition.x == 0 && guardDirection == Direction::LEFT;

  return isExitingTop || isExitingRight || isExitingBottom || isExitingLeft;
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
