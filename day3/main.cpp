#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <vector>

struct Range
{
  int start;
  int end;

  Range(int s, int e) : start(s), end(e) {}
};

std::vector<std::string> split(const std::string& str, char delimiter);
std::string getFileContents(const std::string& filename);
int getProductSum(const std::string& fileContents); // Part 1
int getCondtionalProductSum(const std::string& fileContents);

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

  auto beginDo = std::sregex_iterator(fileContents.begin(), fileContents.end(), doRegex);
  auto endDo = std::sregex_iterator();

  std::cout << "Found " << std::distance(beginDo, endDo) << "Do's\n";
  for (std::sregex_iterator i = beginDo; i != endDo; i++)
  {
    std::smatch match = *i;
    std::cout << "FROM: " << match.position() << "\n";
  }

  auto beginDont = std::sregex_iterator(fileContents.begin(), fileContents.end(), dontRegex);
  auto endDont = std::sregex_iterator();


  std::cout << "Found " << std::distance(beginDont, endDont) << "Dont's\n";
  for (std::sregex_iterator i = beginDont; i != endDont; i++)
  {
    std::smatch match = *i;
    std::cout << "FROM: " << match.position() << "\n";
  }

  // Calculate valid ranges

  std::vector<Range> validRanges;
  std::smatch::difference_type lastDont;

  std::smatch firstDont = *beginDont;
  Range firstValidRange(0, firstDont.position());
  lastDont = firstDont.position();
  validRanges.push_back(firstValidRange);

  for (std::sregex_iterator iter = beginDo; iter != endDo; iter++)
  {
    std::smatch doMatch = *iter;
    int doStart = doMatch.position();

    for (std::sregex_iterator noIter = beginDont; noIter != endDont; noIter++)
    {
      std::smatch dontMatch = *noIter;
      int dontStart = dontMatch.position();

      if (dontStart > lastDont && dontStart > doStart)
      {
        Range nextValidRange(doStart, dontStart);
	validRanges.push_back(nextValidRange);
	lastDont = dontStart;
	break;
      }
    }
  }

  for (int i = 0; i < validRanges.size(); i++)
  {
    std::cout << validRanges[i].start << " , " << validRanges[i].end << "\n";
  }

  auto begin = std::sregex_iterator(fileContents.begin(), fileContents.end(), mulRegex);
  auto end = std::sregex_iterator();

  std::cout << "Found " << std::distance(begin, end) << " matches\n";
  int productsSum = 0;

  for (std::sregex_iterator i = begin; i != end; i++)
  {
    std::smatch match = *i;
    int matchPosition = match.position();
    bool isInValidRange = false;

    // Guard that position is valid!
    // THE BELOW WONT WORK!!!!!!!! ITS THE MOST RECENT THAT MATTERS!
    
    // TODO: FIX RANGE SOLUTION!
    // LOOK AT MATCH POSTION
    // ITERATE DONTS FIND THE CLOSEST THAT IS LESS THAN
    // ITERATE DOS FIND THE CLOSEST THAT IS LESS THAN
    // IF DONT IS CLOSER JUST CONTINUE TO NEXT ITERATION!
    for (Range range : validRanges)
    {
      if (matchPosition > range.start && matchPosition < range.end) 
      {
        isInValidRange = true;
	break;
      }
    }

    if (!isInValidRange)
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
