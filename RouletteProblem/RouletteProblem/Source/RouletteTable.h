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
        RED = 1,
        GREEN = 2
      };

      RouletteResults(Color color,int number)  
      {
        mColor = color;
        mNumber = number;
      }

      friend std::ostream& operator<<(std::ostream& os, const RouletteResults& rouletteResults)
      {
        if(rouletteResults.mColor == RouletteResults::Color::GREEN)
          os << "Color: " << "Green" << std::endl;
        else
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