#pragma once

#include <iostream>

class RouletteTable
{
  public:
    struct RouletteResults
    {
      enum Color
      {
        BLACK = 0,
        RED = 1
      };

      RouletteResults(Color color,int number)  
      {
        mColor = color;
        mNumber = number;
      }

      friend std::ostream& operator<<(std::ostream& os, const RouletteResults& rouletteResults)
      {
        os << "Color: " << (rouletteResults.mColor ? "Red" : "Black") << std::endl;
        os << "Number: " << rouletteResults.mNumber << std::endl;
        return os;
      }

      Color mColor;
      int mNumber;
    };

    RouletteTable() {}
    ~RouletteTable() {}

    RouletteResults Spin();

  private:
};