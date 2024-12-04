#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <vector>

std::vector<std::string> split(const std::string& str, char delimiter);
std::string getFileContents(const std::string& filename);
int getProductSum(const std::string& fileContents); // Part 1
int getCondtionalProductSum(const std::string& fileContents); // Part 2

int main()
{
  std::string fileContents = getFileContents("input.txt");

  if (fileContents.length() == 0)
  {
    std::cout << "No input data found!\n";
    return EXIT_FAILURE;
  }
  
//  int productSum = getProductSum(fileContents);
  int productSum = getCondtionalProductSum(fileContents);

  std::cout << "PRODUCT SUM: " << productSum << "\n";

  return EXIT_SUCCESS;
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

std::string getFileContents(const std::string& filename)
{
  std::ifstream file(filename);

  if (!file)
  {
    std::cout << "Failed to open file: " << filename << "\n";
    return "";
  }

  std::string fileContent;

  while (!file.eof())
  {
    if (file.eof())
    {
      break;
    }
    std::string currentLine; 
    file >> currentLine;
    fileContent = fileContent + currentLine;
  }

  return fileContent;
}

int getProductSum(const std::string& fileContents)
{
  std::regex mulRegex("mul\\([0-9]*,[0-9]*\\)");

  auto begin = std::sregex_iterator(fileContents.begin(), fileContents.end(), mulRegex);
  auto end = std::sregex_iterator();

  std::cout << "Found " << std::distance(begin, end) << " matches\n";
  int productsSum = 0;

  for (std::sregex_iterator i = begin; i != end; i++)
  {
    std::smatch match = *i;
    std::string matchString = match.str();

    std::cout << matchString << "\n";

    // Know that the first 4 letters are mul( and last is ) -- so that is from 4 to length - 1
    std::string buildString;
    for (int j = 4; j < matchString.length() - 1; j++)
    {
      buildString = buildString + matchString[j]; 
    }

    std::vector<std::string> nums = split(buildString, ',');
    for (int k = 0; k < nums.size(); k++)
    {
      std::cout << nums[k] << "\n";
    } 

    int a = stoi(nums[0]);
    int b = stoi(nums[1]);

    productsSum = productsSum + (a * b);
  }

  return productsSum;
}


int getCondtionalProductSum(const std::string& fileContents)
{
  std::regex mulRegex("mul\\([0-9]*,[0-9]*\\)");
  std::regex doRegex("do\\(\\)");
  std::regex dontRegex("don't\\(\\)");

  std::vector<int> doPositions;
  std::vector<int> dontPositions;

  auto beginDo = std::sregex_iterator(fileContents.begin(), fileContents.end(), doRegex);
  auto endDo = std::sregex_iterator();

  std::cout << "Found " << std::distance(beginDo, endDo) << "Do's\n";
  for (std::sregex_iterator i = beginDo; i != endDo; i++)
  {
    std::smatch match = *i;
    std::cout << "FROM: " << match.position() << "\n";
    doPositions.push_back(match.position());
  }

  auto beginDont = std::sregex_iterator(fileContents.begin(), fileContents.end(), dontRegex);
  auto endDont = std::sregex_iterator();

  std::cout << "Found " << std::distance(beginDont, endDont) << "Dont's\n";
  for (std::sregex_iterator i = beginDont; i != endDont; i++)
  {
    std::smatch match = *i;
    std::cout << "FROM: " << match.position() << "\n";
    dontPositions.push_back(match.position());
  }

  auto begin = std::sregex_iterator(fileContents.begin(), fileContents.end(), mulRegex);
  auto end = std::sregex_iterator();

  std::cout << "Found " << std::distance(begin, end) << " matches\n";
  int productsSum = 0;

  for (std::sregex_iterator i = begin; i != end; i++)
  {
    std::smatch match = *i;
    int matchPosition = match.position();

    int closestDont = 0;
    int closestDo = 0;
    
    for (int dontPosition : dontPositions)
    {
      if (dontPosition > matchPosition)
      {
        break;
      }
      else 
      {
        closestDont = dontPosition;  
      }
    }

    for (int doPosition : doPositions)
    {
      if (doPosition > matchPosition)
      {
        break;
      }
      else 
      {
        closestDo = doPosition;  
      }
    }

    if (closestDont > closestDo)
    {
      std::cout << "NOT IN VALID RANGE!! " << match.position() << "\n";
      continue;
    }
    std::cout << "IN VALID RANGE!! " << match.position() << "\n";
    std::string matchString = match.str();
    std::cout << matchString << "\n";

    // Know that the first 4 letters are mul( and last is ) -- so that is from 4 to length - 1
    std::string buildString;
    for (int j = 4; j < matchString.length() - 1; j++)
    {
      buildString = buildString + matchString[j]; 
    }
    std::vector<std::string> nums = split(buildString, ',');

    for (int k = 0; k < nums.size(); k++)
    {
      std::cout << nums[k] << "\n";
    } 
   
    int a = stoi(nums[0]);
    int b = stoi(nums[1]);

    productsSum = productsSum + (a * b);
  }

  return productsSum;
}
