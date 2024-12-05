#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Rule
{
  std::vector<int> mPageNumbers;
  int mBeforeCount = 0; 
 public:
  void addBeforePage(int before);
  void addAfterPage(int after);

  bool isPageBefore(int page);
  bool isPageAfter(int page);
};

void Rule::addBeforePage(int before)
{
  mPageNumbers.insert(mPageNumbers.begin(), before);
  mBeforeCount++;
}

void Rule::addAfterPage(int after)
{
  mPageNumbers.push_back(after);
}

bool Rule::isPageBefore(int page)
{
  for (int i = 0; i < mBeforeCount; i++)
  {
    if (mPageNumbers[i] == page)
    {
      return true;
    }
  }   
  
  return false;
}

bool Rule::isPageAfter(int page)
{
  for (int i = mBeforeCount; i < mPageNumbers.size(); i++)
  {
    if (mPageNumbers[i] == page)
    {
      return true;
    }
  }
  
  return false;
}

std::vector<std::string> getFileLines(const std::string& filename);
std::map<int, Rule> getPageNumberToRuleMap(const std::vector<std::string> fileLines);
std::vector<std::string> split(const std::string& str, char delimiter);

int main()
{
  std::vector<std::string> fileLines = getFileLines("testInput.txt");

  if (fileLines.size() == 0)
  {
    std::cout << "NO FILE INPUT FOUND!\n";
    return EXIT_FAILURE;
  }

  std::cout << "FILE LINES: \n";
  for (std::string line : fileLines)
  {
    std::cout << line << "\n";
  }

  std::vector<std::string> instructionLines;
  std::vector<std::string> pageNumberLines;

  for (std::string line : fileLines)
  {
    for (char c : line)
    {
      if (c == '|') 
      {
        instructionLines.push_back(line);
	break;
      }

      if (c == ',')
      {
        pageNumberLines.push_back(line);
	break;
      }
    }
  }

  // Parse instructions

  std::map<int, Rule> pageNumberToRule;

  for (std::string instruction : instructionLines)
  {
    std::vector<std::string> nums = split(instruction, '|');

    int lhNum = stoi(nums[0]);
    int rhNum = stoi(nums[1]);

    if (pageNumberToRule.count(lhNum) == 1) {
      pageNumberToRule[lhNum].addAfterPage(rhNum);
    }
    else
    {
      Rule newRule;
      newRule.addAfterPage(rhNum);
      pageNumberToRule[lhNum] = newRule;
    }


    if (pageNumberToRule.count(rhNum) == 1) {
      pageNumberToRule[rhNum].addBeforePage(lhNum);
    }
    else
    {
      Rule newRule;
      newRule.addBeforePage(lhNum);
      pageNumberToRule[rhNum] = newRule;
    }

  }

  for (std::string pageNumberLine : pageNumberLines)
  {
    std::vector<std::string> nums = split(pageNumberLine, ',');

    std::vector<int> pageNumbers;
    for (std::string num : nums)
    {
      pageNumbers.push_back(stoi(num));
    }

    for (int i = 0; i < pageNumbers.size(); i++)
    {
      // Check before pages
      // Check after pages

      std::cout << "PAGE NUMBER: " << pageNumbers[i] << "\n";

      for (int j = i + 1; j < pageNumbers.size(); j++)
      {
      }
    }
  }
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

std::vector<std::string> split(const std::string& str, char delimiter)
{
  std::string buildString;
  std::vector<std::string> results;

  for (int i = 0; i < str.length(); i++)
  {
    char currentChar = str[i];
    if (currentChar == delimiter)
    {
       results.push_back(buildString);
       buildString = "";
    }
    else
    {
       buildString = buildString + currentChar;
    }
  }

  if (buildString.length() != 0)
  {
    results.push_back(buildString);
  }

  return results;
}
