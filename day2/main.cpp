#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& s, char delimiter);
std::vector<std::string> getFileLines(const std::string& filename);
int getSafeLevelCount(const std::vector<std::string>& fileLines); // Part 1
int getDampendSafeLevelCount(const std::vector<std::string>& fileLines); // Part 2

int main()
{
  std::vector<std::string> fileLines = getFileLines("input.txt");

  if (fileLines.size() == 0)
  {
    std::cout << "NO INPUT DATA FOUND!\n";
    return EXIT_FAILURE;
  }

  // part 1
  int safeCount = getSafeLevelCount(fileLines);
  std::cout << "SAFE COUNT: " << safeCount << "\n";
  
  return EXIT_SUCCESS;
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
  std::vector<std::string> result;
  std::string buildString = "";

  for (int i = 0; i < s.length(); i++)
  {
    char curr = s[i];
    if (curr == delimiter)
    {
      result.push_back(buildString);
      buildString = "";
    } 
    else 
    {
      buildString = buildString + curr;
    }
  }

  if (buildString.length() != 0)
  {
    result.push_back(buildString);
  }

  return result;
}

std::vector<std::string> getFileLines(const std::string& filename)
{
  std::ifstream file(filename);
  std::vector<std::string> lines;

  if (!file)
  {
    std::cout << "FAILED OPENING FILE: " << filename << "\n";
    return lines;
  }
  
  std::string line;
  while (std::getline(file, line))
  { 
    lines.push_back(line);
  }

  file.close();

  return lines;
}

int getSafeLevelCount(const std::vector<std::string>& fileLines)
{
  int safeCount = 0;
  for (int i = 0; i < fileLines.size(); i++)
  {
    std::string line = fileLines[i];
    std::vector<std::string> components = split(line, ' ');
    std::vector<int> nums;

    for (std::string component : components)
    {
      nums.push_back(stoi(component));
    }

    std::cout << "Inspecting level " << i << "\n";

    bool isDecreasing = nums[0] > nums[1];

    if (isDecreasing)
    {
       std::cout << "This level should be DECREASING!\n";
    }
    else
    {
      std::cout << "This level should be INCREASING!\n";  
    }

    int previous = -1;
    for (int j = 0; j < nums.size(); j++)
    {
      int current = nums[j];

      std::cout << "INSPECTING: " << current << "\n";
      if (previous == -1)
      {
        previous = current;
      }
      else 
      {
        std::cout << "PREVIOUS: " << previous << "\n";
        int delta = std::abs(current - previous);
        std::cout << "DELTA: " << delta << "\n";

        if ((isDecreasing && current > previous) || (!isDecreasing && current < previous) || current == previous || (delta < 1 || delta > 3))
        {
          std::cout << "LEVEL FAILED!\n";
          break;
        }
        
        if (j == nums.size() - 1)
        {
          std::cout << "INCREMENTING SAFE COUNT\n";
          safeCount++;
        }

        // Keep going! So far so good if here!
        std::cout << "PREVIOUS = " << current << "\n";
        previous = current;
      }
    }
  }

  return safeCount;
}


int getDampendSafeLevelCount(const std::vector<std::string>& fileLines)
{
  int safeCount = 0;
  for (int i = 0; i < fileLines.size(); i++)
  {
    std::string line = fileLines[i];
    std::vector<std::string> components = split(line, ' ');
    std::vector<int> nums;

    std::cout << "Inspecting level " << i << "\n";

    for (std::string component : components)
    {
      nums.push_back(stoi(component));
      std::cout << component << " ";
    }
    std::cout << "\n";

    bool isDecreasing = nums[0] > nums[1];

    if (isDecreasing)
    {
       std::cout << "This level should be DECREASING!\n";
    }
    else
    {
      std::cout << "This level should be INCREASING!\n";  
    }

    int previous = -1;
    for (int j = 0; j < nums.size(); j++)
    {
      int current = nums[j];

      std::cout << "INSPECTING: " << current << "\n";
      if (previous == -1)
      {
        previous = current;
      }
      else 
      {
        std::cout << "PREVIOUS: " << previous << "\n";
        int delta = std::abs(current - previous);
        std::cout << "DELTA: " << delta << "\n";

        if ((isDecreasing && current > previous) || (!isDecreasing && current < previous) || current == previous || (delta < 1 || delta > 3))
        {
          std::cout << "LEVEL FAILED!\n";
          break;
        }
        
        if (j == nums.size() - 1)
        {
          std::cout << "INCREMENTING SAFE COUNT\n";
          safeCount++;
        }

        // Keep going! So far so good if here!
        std::cout << "PREVIOUS = " << current << "\n";
        previous = current;
      }
    }
  }

  return safeCount;



}
