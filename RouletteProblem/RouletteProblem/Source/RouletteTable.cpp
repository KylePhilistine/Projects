#include "RouletteTable.h"
#include <random>
#include <chrono>

RouletteTable::RouletteResults RouletteTable::Spin()
{
    // seed the random engine with the current time using the chrono library
  std::default_random_engine roulettecolorGenerator(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> colorDistribution(0, 1);
  std::uniform_int_distribution<int> numberDistribution(0, 37);

  int spinResultColor = colorDistribution(roulettecolorGenerator);
  int spinResultNumber = numberDistribution(roulettecolorGenerator);

  return RouletteResults((RouletteResults::Color)spinResultColor, spinResultNumber);
}

