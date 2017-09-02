#include "RouletteTable.h"
#include <random>
#include <chrono>

RouletteTable::RouletteResults RouletteTable::Spin()
{
    // seed the random engine with the current time using the chrono library
  std::default_random_engine roulettecolorGenerator((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> colorDistribution(0, 1);
  std::uniform_int_distribution<int> numberDistribution(0, 37);

  int spinResultColor = colorDistribution(roulettecolorGenerator);
  int spinResultNumber = numberDistribution(roulettecolorGenerator);

    // if the number is 0 or 00(37) then the color is Green and if you bet red/black you will lose
  return RouletteResults((spinResultNumber == 0 || spinResultNumber == 37) ? RouletteResults::Color::GREEN : (RouletteResults::Color)spinResultColor, spinResultNumber);
}

