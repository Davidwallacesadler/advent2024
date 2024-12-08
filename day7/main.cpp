#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

struct CalibrationEquation
{
  long result = 0;
  std::vector<long> components;
};

struct CrappyDynamicBitset
{
  std::vector<bool> bits;

  CrappyDynamicBitset(int bitCount)
  {
    for (int i = 0; i < bitCount; i++)
    {
      bits.push_back(false);
    }
  }

  void increment() 
  {
    // Walk until we hit a 0. When hit set a 1 and flip all previous bits
    for (int i = 0; i < bits.size(); i++)
    {
      if (!bits[i])
      {
        bits[i] = true;
        for (int j = 0; j < i; j++)
        {
          bits[j] = false;
        }
        break;
      }
    }
  }

  void print()
  {
    for (int i = 0; i < bits.size(); i++)
    {
      std::cout << bits[i];
    }
    std::cout << "\n";
  }
};

 enum TriState
{
    OFF, NEUTRAL, ON
};

struct CrappyTriset
{
    std::vector<TriState> states;
    
    CrappyTriset(int stateCount)
    {
        for (int i = 0; i < stateCount; i++)
        {
            states.push_back(TriState::OFF);
        }
    }
    
    void increment()
    {
        bool previousWasOn = false;
        for (int i = 0; i < states.size(); i++)
        {
            if (states[i] == TriState::OFF)
            {
                states[i] = TriState::NEUTRAL;
                if (previousWasOn)
                {
                    // Rollover previous
                    for (int j = 0; j < i; j++)
                    {
                        states[j] = TriState::OFF;
                    }
                }
                break;
            }
            if (states[i] == TriState::NEUTRAL)
            {
                states[i] = TriState::ON;
                if (previousWasOn)
                {
                    // Rollover previous
                    for (int j = 0; j < i; j++)
                    {
                        states[j] = TriState::OFF;
                    }
                }
                break;
            }
            
            // If we get here we are rolling over
            previousWasOn = true;
        }
    }
    
    void print()
    {
      for (int i = 0; i < states.size(); i++)
      {
          char c;
          switch (states[i])
          {
              case TriState::OFF:
              c = '0';
              break;
              case TriState::NEUTRAL:
              c = 'N';
              break;
              case TriState::ON:
              c = '1';
          }
          
          std::cout << c;
      }
      std::cout << "\n";
    }
};


std::vector<std::string> getFileLines(const std::string& filename);


int main()
{
  std::vector<std::string> fileLines = getFileLines("input.txt");
  std::vector<CalibrationEquation> equations;

  for (std::string line : fileLines)
  {
    CalibrationEquation equation;
    std::string buildString;
    for (int i = 0; i < line.length(); i++)
    {
      char c = line[i];
      if (c == ':')
      {
        equation.result = stol(buildString);
        buildString = "";
        continue;
      }
      if (c == ' ' && buildString.length() > 0)
      {
        equation.components.push_back(stol(buildString));
        buildString = "";
        continue;
      }
      buildString = buildString + c;
    }
    if (buildString.length() > 0)
    { 
      equation.components.push_back(stol(buildString));
    }

    std::cout << "EQUATION: " << equation.result << " = ";
    for (int compnent : equation.components)
    {
      std::cout << compnent << " ";
    }
    std::cout << "\n";

    equations.push_back(equation);
  }
  
  // Now need to get the operands... All possible positions
  // Thinking of approaching this like a number increasing in binary since we only have 2 operands
  // 000 -> 100 -> 010 -> 110 -> 001 -> 101 -> 011 -> 111 (0 = +, 1 = *)
  // Vector of bools? lol seems ridiculous (Each one representing the state above)
  // Loop condition: Until 2^length
  
  long totalValidCalibrationSum = 0;
  for (CalibrationEquation equation : equations)
  {
    int totalPossibilities = std::pow(3, equation.components.size() - 1);
    // CrappyDynamicBitset bitset(equation.components.size() - 1);
    CrappyTriset triset(equation.components.size() - 1);

    std::cout << "TOTAL POSSIBILITIES: " << totalPossibilities << "\n";

    for (int i = 0; i < totalPossibilities; i++)
    {
      long runningValue = 0;

      std::cout << "\n";

      std::cout << "CALCULATING WITH TRISET:";
      // bitset.print();
      triset.print();

      for (int j = 0; j < equation.components.size(); j++)
      {
        long currentValue = equation.components[j];
        if (runningValue == 0)
        {
          runningValue = currentValue;
        }
        else 
        {
          // bool shouldMultiply = bitset.bits[j - 1];
          switch (triset.states[j - 1])
          {
            case TriState::OFF:
            std::cout << "ADDING: " << runningValue << " + " << currentValue << "\n";
            runningValue = runningValue + currentValue; 
            break;

            case TriState::NEUTRAL:
              {
                std::cout << "ORing: " << runningValue << " || " << currentValue << "\n";

                std::string lhs;
                lhs = std::to_string(runningValue);
                std::string rhs;
                rhs = std::to_string(currentValue);

                runningValue = stol(lhs + rhs);
                break;
              }

            case TriState::ON:
            std::cout << "MUTITPLYING: " << runningValue << " * " << currentValue << "\n";
            runningValue = runningValue * currentValue;
          }
        }
      }

      if (runningValue == equation.result)
      {
        std::cout << "FOUND MATCH!\n";
        totalValidCalibrationSum = totalValidCalibrationSum + equation.result;
        break;
      }

      std::cout << "CALCULATION FAILED! " << equation.result << " != " << runningValue << "\n";

      // Prepare state for next iteration
      // bitset.increment();
      triset.increment();
    }
  }

  std::cout << "TOTAL VALID CALIBRATION SUM: " << totalValidCalibrationSum << "\n";

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
