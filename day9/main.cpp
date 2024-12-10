#include <iostream>
#include <fstream>
#include <string>

std::string getFileLine(const std::string& filename);
long disgustingSolution(const std::string& fileLine);

int main()
{
  std::string fileLine = getFileLine("input.txt");

  long checksum = disgustingSolution(fileLine);

  std::cout << "CHECKSUM: " << checksum << "\n";

  return EXIT_SUCCESS;
}

std::string getFileLine(const std::string& filename)
{
  std::ifstream file(filename);

  if (!file)
  {
    std::cout << "FAILED TO OPEN FILE: " << filename << "\n";
    return "";
  }

  std::string fileLine;
  while (!file.eof())
  {
    file >> fileLine;
  }

  return fileLine;
}

struct FileBlock
{
  int fileId;

  FileBlock(): fileId(-1) {}
  FileBlock(int id): fileId(id) {}
};

// May the unicode gods have mercy on my soul... 
long disgustingSolution(const std::string& fileLine)
{
  std::vector<FileBlock> fileBlocks;
  int currentFileId = 0;

  for (int i = 0; i < fileLine.size(); i++)
  {
    char currentChar = fileLine[i];
    int currentValue = currentChar - '0';

    if (i % 2 == 0)
    {
      // FILE
      for (int j = 0; j < currentValue; j++)
      {
        fileBlocks.push_back(FileBlock(currentFileId));
      }
      currentFileId++;
    }
    else
    {
      // FREE SPACE
      for (int j = 0; j < currentValue; j++)
      {
        fileBlocks.push_back(FileBlock());
      }
    }
  }
  
  int currentEmptyIndex = 0;
  int currentFileIndex = fileBlocks.size() - 1;

  for (int i = 0; i < fileBlocks.size(); i++)
  {
    if (fileBlocks[i].fileId == -1)
    {
      currentEmptyIndex = i;
      break;
    }
  }

  while (currentEmptyIndex < currentFileIndex)
  {
    // Swap the values
    fileBlocks[currentEmptyIndex] = fileBlocks[currentFileIndex];
    fileBlocks[currentFileIndex] = FileBlock();

    // Recalculate empty index
    for (int i = currentEmptyIndex; i < fileBlocks.size(); i++)
    {
      if (fileBlocks[i].fileId == -1)
      {
        currentEmptyIndex = i;
	    break;
      }
    }

    // Recalculate file index
    for (int i = currentFileIndex; i > 0; i--)
    {
      if (fileBlocks[i].fileId != -1)
      {
        currentFileIndex = i;
 	    break;
      }
    }
  }
  
  long checksum = 0;
  for (int i = 0; i < fileBlocks.size(); i++)
  {
    if (fileBlocks[i].fileId == -1)
    {
      break;
    }

    std::cout << fileBlocks[i].fileId << " * " << i << "\n";

    long product = fileBlocks[i].fileId * i;

    checksum = checksum + product;

    std::cout << checksum << "\n";
  }
  
  return checksum;
}

// TODO: Figure out how to use unicode chars in C++... I have no idea how to do that right now
int initialSolution()
{
  std::string fileLine = getFileLine("input.txt");

  if (fileLine.length() == 0)
  {
    std::cout << "NO INPUT DATA FOUND!\n";
    return EXIT_FAILURE;
  }

  std::cout << fileLine << "\n";

  // Construct file block representation
  int currentFileId = 0;
  std::string blockRepresentation;

  for (int i = 0; i < fileLine.size(); i++)
  {
    char currentChar = fileLine[i];
    int currentValue = currentChar - '0';

    if (i % 2 == 0)
    {
      // FILE
      char fileId = '0' + currentFileId;

      // IDEA: USE ASCII?? WILL THIS WORK?! 
      for (int j = 0; j < currentValue; j++)
      {
        blockRepresentation = blockRepresentation + fileId;
      }

      // TODO: How to handle two digit ID?!?!
      currentFileId++;
    }
    else
    {
      // FREE SPACE
      for (int j = 0; j < currentValue; j++)
      {
        blockRepresentation = blockRepresentation + '.';
      }
    }
  }

  std::cout << "BLOCK REPRESENTAITON: " << blockRepresentation << "\n";

  int currentEmptyIndex = 0;
  int currentFileIndex = blockRepresentation.length() - 1;

  for (int i = 0; i < blockRepresentation.length(); i++)
  {
    if (blockRepresentation[i] == '.')
    {
      currentEmptyIndex = i;
      break;
    }
  }

  while (currentEmptyIndex < currentFileIndex)
  {
    // Swap the values
    blockRepresentation[currentEmptyIndex] = blockRepresentation[currentFileIndex];
    blockRepresentation[currentFileIndex] = '.';

    // Recalculate empty index
    for (int i = currentEmptyIndex; i < blockRepresentation.length(); i++)
    {
      if (blockRepresentation[i] == '.')
      {
        currentEmptyIndex = i;
	break;
      }
    }

    // Recalculate file index
    for (int i = currentFileIndex; i > 0; i--)
    {
      if (blockRepresentation[i] != '.')
      {
        currentFileIndex = i;
	break;
      }
    }
  }

  std::cout << "COMPACT BLOCK: " << blockRepresentation << "\n";

  int checksum = 0;
  for (int i = 0; i < blockRepresentation.length(); i++)
  {
    if (blockRepresentation[i] == '.')
    {
      break;
    }

    int value = '0' + blockRepresentation[i];
    checksum = checksum + (value * i);
  }

  std::cout << "CHECKSUM: " << checksum << "\n";

  return checksum;
}
