#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& s, char delimiter);

int main()
{
  std::string fileName = "input.txt";
  std::ifstream file(fileName);

  if (!file)
  {
    std::cout << "Failed to open input file\n";
    return EXIT_FAILURE;
  }

  std::string line;
  std::vector< std::vector<int> > levels;

  while (std::getline(file, line))
  { 
    std::vector<std::string> nums = split(line, ' ');

    std::vector<int> level;
    for (int i = 0; i < nums.size(); i++)
    {
      int num = stoi(nums[i]);
      level.push_back(num);
    }

    levels.push_back(level);
  }
  file.close();

  // part 1
  int safeCount = 0;
  for (int i = 0; i < levels.size(); i++)
  {
    std::vector<int> nums = levels[i];

    std::cout << "Inspecting level " << i << "\n";

    bool isDecreasing = true;
    if (nums[0] < nums[1])
    {
      isDecreasing = false;
    }

    std::cout << "should be decreasing " << isDecreasing << "\n";

    int previous = -1;
    bool hasFailedOnce = false;
    for (int j = 0; j < nums.size(); j++)
    {
      int current = nums[j];


         std::cout << "Previous: " << previous << ", " << "Current: " << current << "\n";

      if (previous == -1)
      {
        previous = current;
      }
      else 
      {
        int delta = std::abs(current - previous);

        if ((isDecreasing && current > previous) || (!isDecreasing && current < previous) || current == previous || (delta < 1 || delta > 3))
        {

          if (hasFailedOnce) {
            std::cout << "SECOND FAILURE\n";
            break;
          } else {
            std::cout << "FIRST FAILURE at" << j << "\n";
            hasFailedOnce = true;
            //previous = current;

            if (j == 1) {
              std::cout << "recalculating decresing state\n";
              isDecreasing = nums[0] > nums[2];
              
            }
            // Recaclulate trend
            //
            if (j == nums.size() - 1)
            {
              std::cout << "INCREMENTING SAFE COUNT\n";
              safeCount++;
            }
            std::cout << "CONTINUE\n";
            continue; // keep previous value the same!
          }



          //break;
        }

        
        if (j == nums.size() - 1)
        {
          std::cout << "INCREMENTING SAFE COUNT\n";
          safeCount++;
        }

        // Keep going! So far so good if here!
        std::cout << "UPDATING PREVIOUS\n";
        previous = current;
      }
    }
  }

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
