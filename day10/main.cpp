#include<iostream>
#include<fstream>
#include<string>
#include<vector>

std::vector<std::string> getFileLines(const std::string& filename);

int main()
{
  std::vector<std::string> fileLines = getFileLines("testInput2.txt");

  if (fileLines.size() == 0)
  {
    std::cout << "NO INPUT DATA FOUND!\n";
    return EXIT_FAILURE;
  }

  for (int i = 0; i < fileLines.size(); i++)
  {
    std::cout << fileLines[i] << "\n";
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
