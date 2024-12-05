#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

std::vector<std::string> getFileLines(const std::string& filename);
int getMatchCount(const std::vector<std::string>& lines);
std::vector<std::string> getVerticalLines(const std::vector<std::string>& lines);
std::vector<std::string> getVerticallyRotatedLines(const std::vector<std::string>& lines);
std::vector<std::string> getLeftToRightDiagonalLines(const std::vector<std::string>& lines);

int main()
{
  std::vector<std::string> fileLines = getFileLines("input.txt");

  if (fileLines.size() == 0)
  {
     std::cout << "NO INPUT DATA FOUND!\n";
     return EXIT_FAILURE;
  }
  
  std::cout << "FILE HAS " << fileLines.size() << " LINES\n";
  for (int i = 0; i < fileLines.size(); i++)
  {
     std::cout << "Line: " << i << ", Content: " << fileLines[i] << "\n";
  }

  // Look at horiztonal
  // Look at vertical
  // Create LTR diagonal lines
  // Create RTL diagonal lines

  int horizontalMatches = getMatchCount(fileLines);

  std::cout << "FOUND " << horizontalMatches << " HORIZONTAL MATCHES\n";

  std::vector<std::string> verticalLines = getVerticalLines(fileLines);
  
  std::cout << "VERTICAL LINES:\n";
  for (int i = 0; i < verticalLines.size(); i++)
  {
    std::cout << verticalLines[i] << "\n";
  }

  int verticalMatches = getMatchCount(verticalLines);

  std::cout << "FOUND " << verticalMatches << " VERTICAL MATCHES\n";

  std::cout << "Getting Diagonal...\n";

  std::vector<std::string> ltrDiagonalLines = getLeftToRightDiagonalLines(fileLines);

  for (int i = 0; i < ltrDiagonalLines.size(); i++)
  {
    std::cout << ltrDiagonalLines[i] << "\n";
  }
  int ltrDiagonalMatches = getMatchCount(ltrDiagonalLines);

  std::cout << "FOUND " << ltrDiagonalMatches << " LTR DIAGONAL MATCHES\n";

  std::vector<std::string> verticallyFlippedLines = getVerticallyRotatedLines(fileLines);

  std::vector<std::string> rtlDiagonalLines = getLeftToRightDiagonalLines(verticallyFlippedLines);

  for (int i = 0; i < rtlDiagonalLines.size(); i++)
  {
    std::cout << rtlDiagonalLines[i] << "\n";
  }

  int rtlDiagonalMatches = getMatchCount(rtlDiagonalLines);

  std::cout << "FOUND " << rtlDiagonalMatches << " RTL DIAGONAL MATCHES\n";
  
  int totalMatchCount = horizontalMatches + verticalMatches + ltrDiagonalMatches + rtlDiagonalMatches;

  std::cout << "TOTAL MATCHES: " << totalMatchCount << "\n";
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

  while (std::getline(file, currentLine))
  {
    results.push_back(currentLine); 
  }

  return results;
}

int getMatchCount(const std::vector<std::string>& lines)
{
  int matchCount = 0;

  for (std::string line : lines)
  {
    std::regex xmasRegex("XMAS");
    std::regex samxRegex("SAMX");

    std::sregex_iterator xmasStart(line.begin(), line.end(), xmasRegex);
    std::sregex_iterator xmasEnd;
    int xmasMatchCount = std::distance(xmasStart, xmasEnd);

    std::cout << "Found " << xmasMatchCount << " XMAS's\n";

    std::sregex_iterator samxStart(line.begin(), line.end(), samxRegex);
    std::sregex_iterator samxEnd;
    int samxMatchCount = std::distance(samxStart, samxEnd);

    std::cout << "Found " << samxMatchCount << " SAMX's\n";

    matchCount = matchCount + (xmasMatchCount + samxMatchCount);
  }

  return matchCount;
}

std::vector<std::string> getVerticalLines(const std::vector<std::string>& lines)
{
  std::vector<std::string> results;
  
  for (int col = 0; col < lines[0].length(); col++)
  {
    std::string buildString;

    for (int row = 0; row < lines.size(); row++)
    {
      buildString = buildString + lines[row][col];
    }

    results.push_back(buildString);
  }
  
  return results;
}

std::vector<std::string> getLeftToRightDiagonalLines(const std::vector<std::string>& lines)
{
  std::vector<std::string> results;
  int row = 0;
  int col = 0;

  // Top left corner to middle
  int lastRow = 0;

  while (lastRow < lines.size())
  {
    std::string buildString;
  
    while (row > 0)
    {
      char currentChar = lines[row][col];
      buildString = buildString + currentChar;
      col++;
      row--;
    }

    char currentChar = lines[row][col];
    buildString = buildString + currentChar;
    results.push_back(buildString);

    col = 0;
    row = lastRow + 1;
    lastRow++;
  }

  // Left of middle to bottom right corner
  row = lines.size() - 1;
  col = 1;

  int lastCol = 1;
  int maxCol = lines[0].size();


  while (lastCol < maxCol)
  {
    std::string buildString;

    while (col < maxCol)
    {
      char currentChar = lines[row][col];
      buildString = buildString + currentChar;
      col++;
      row--;
    }
    
    results.push_back(buildString);
    col = lastCol + 1;
    row = lines.size() - 1;
    lastCol++;
  }



  return results;
}

std::vector<std::string> getVerticallyRotatedLines(const std::vector<std::string>& lines)
{
  std::vector<std::string> results;
  
  for (std::string line : lines)
  {
    std::string reversed;
    std::copy(line.crbegin(), line.crend(), std::back_inserter(reversed));
    results.push_back(reversed);
  }

  return results;
}
