#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unordered_map>

// https://adventofcode.com/2024/day/1

// Part 1: Sort the two columns and then compute the diff between left and right side, then add up
// Part 2: Calculate similarity score. Count how many times the element on the left shows up in the list on the right, multiply the number by this factor, then add up

int calculateTotalDistance(std::vector<int>& lhList, std::vector<int>& rhList);
void sortAscending(std::vector<int>& list);
int calculateSimilarityScore(const std::vector<int>& lhList, const std::vector<int>& rhList);

int main()
{
  // Lets start by reading the inputFile
  std::string filename = "input.txt";
  std::ifstream inputFile(filename);
  
  // Make sure we opened the file properly
  if (!inputFile)
  {
    std::cout << "Could not open file: " + filename + "\n";
    return EXIT_FAILURE;
  }

  // Setup stuff for reading data
  std::vector<int> lhValues;
  std::vector<int> rhValues;
  int currentIndex = 0;

  // Read nums from the file
  while (!inputFile.eof())
  {
    int currentNum;
    inputFile >> currentNum;

    if (inputFile.eof())
    {
      break;
    }

    if (currentIndex % 2 == 0)
    {
      lhValues.push_back(currentNum);
    }
    else 
    {
      rhValues.push_back(currentNum);
    }

    currentIndex++;
  }

  // Part 1
  //int totalDistance = calculateTotalDistance(lhValues, rhValues);
  //std::cout << "TOTAL DISTANCE: " << totalDistance << "\n";
  //
  
  // Part 2
  int similarityScore = calculateSimilarityScore(lhValues, rhValues);
  std::cout << "SIMILARITY SCORE: " << similarityScore << "\n";
  
  return EXIT_SUCCESS;
}

// A super shitty bubble sort :)
void sortAscending(std::vector<int>& list)
{
  int i = 0;
  int j = 0;
  int last = -1;
  
  while (j < list.size()) 
  {
    while (i < list.size())
    {
      int curr = list[i];
      if (last != -1)
      {
        if (curr < last)
        {
          list[i] = last;
          list[i - 1] = curr;
          i++;
          continue;
        }
      }
      
      last = curr;
      i++;
    }

    i = 0;
    last = -1;
    j++;
  }
}

// PART 1
int calculateTotalDistance(std::vector<int>& lhList, std::vector<int>& rhList)
{
  // Sort both lists so that it starts at the smallest and gets bigger
  sortAscending(lhList);
  sortAscending(rhList);

  // Compare all the sorted values and add to the running total 
  int totalDistance = 0;
  for (int i = 0; i < lhList.size(); i++)
  {
    int lhValue = lhList[i];
    int rhValue = rhList[i];

    totalDistance = totalDistance + std::abs(lhValue - rhValue);
  }

  return totalDistance;
}

// PART 2
int calculateSimilarityScore(const std::vector<int>& lhList, const std::vector<int>& rhList)
{
  std::unordered_map<int, int> numberToCount;
  
  // Count the occurences of nums in the rhList
  for (int i = 0; i < rhList.size(); i++)
  {
    int num = rhList[i];
    if (numberToCount.count(num) == 1)
    {
      numberToCount[num] = numberToCount[num] + 1;
    }
    else 
    {
      numberToCount[num] = 1;
    }
  }
  
  // Count how many times the lh value shows up in rh list, multiply, and total
  int similarityScore = 0;
  for (int i = 0; i < lhList.size(); i++)
  {
    int num = lhList[i];
    int count = 0;
    if (numberToCount.count(num) == 1)
    {
      count = numberToCount[num];
    }
    similarityScore = similarityScore + (num * count);
  }

  return similarityScore;
}
