#include <iostream>
#include <string>
#include <vector>


int main()
{
  // Line of stones each with a number that changes on each blink
  // Either the number changes or the stone splits into 2

  // Stones change according to the first true statement below
  // 1. Stones with 0 change numbers to 1
  // 2. Stones with even number: replaced by 2 stones with the digits split (1000 -> 10 0)
  // 3. Lastly if not 1. or 2. replace the stone with the old number multiplied by 2024 (1 -> 2048)

  // No matter how stones change the order is preserved

  // How many stones do we have when we blink 25 times?
  //std::vector<long> stones = {125, 17};
  std::vector<long> stones = {5688, 62084, 2, 3248809, 179, 79, 0, 172169};

  int blinkCount = 25;

  for (int i = 0; i < blinkCount; i++)
  {
    int j = 0;

    std::cout << "LOOKING BEFORE BLINK: \n";
    //for (int k = 0; k < stones.size(); k++)
    //{
    //  std::cout << " , " << stones[k];
    //}
    std::cout << "\n";

    std::cout << "---- BLINK ----\n";

    while (j < stones.size())
    {
      int stone = stones[j];
      std::string digits = std::to_string(stones[j]);

      std::cout << "LOOKING AT STONE WITH NUMBER: " << stone << "\n";

      if (stone == 0)
      {
        std::cout << "ZERO STONE\n";

        stones[j] = 1;
	j++;
      }
      else if (digits.size() % 2 == 0)
      {
        std::cout << "EVEN STONE\n";

	long mid = digits.size() / 2;

	std::string lhs = digits.substr(0, mid);
	std::string rhs = digits.substr(mid, digits.size());

	std::cout << "LHS: " << lhs << "\n";
	std::cout << "RHS: " << rhs << "\n";

	std::vector<int> everythingAfter;

	std::cout << "EVERYTHING AFTER: \n";

	for (int k = j + 1; k < stones.size(); k++)
	{
	  everythingAfter.push_back(stones[k]);
	  //std::cout << ", " << stones[k];
	}
	std::cout << "\n";

	stones.erase(stones.begin() + j, stones.end());

	std::cout << "AFTER ERASING: \n";

	//for (int k = 0; k < stones.size(); k++)
	//{
	//  std::cout << ", " << stones[k];
	//}
	std::cout << "\n";

	stones.push_back(stol(lhs));
	stones.push_back(stol(rhs));

	for (int k = 0; k < everythingAfter.size(); k++)
	{
	  stones.push_back(everythingAfter[k]);
	}

	std::cout << "AFTER RE-ALIGNING: \n";

	//for (int k = 0; k < stones.size(); k++)
	//{
	//  std::cout << ", " << stones[k];
	//}
	//std::cout << "\n";

	// Skip the new split stone
	j = j + 2;
      }
      else
     {
        std::cout << "2024 STONE\n";

        stones[j] = stones[j] * 2024;
	j++;
      }
    }
  }
  

  //for (int i = 0; i < stones.size(); i++)
  //{
  //  std::cout << stones[i] << "\n";
  //}


  std::cout << "TOTAL STONES: " << stones.size() << "\n";


  return EXIT_FAILURE;
}


