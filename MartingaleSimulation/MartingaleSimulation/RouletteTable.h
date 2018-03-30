#pragma once

#include <random>  // needed for creating a random number generator
#include <chrono> // seeding random engine
#include <string>

class RouletteTable {
  public:

    enum RouletteTableType {
      SingleZeroWheel = 0,
      DoubleZeroWheel
    };

    struct RouletteResult {
      public:
        enum RouletteColor {
          Red = 0,
          Black,
          Zero, // Green
          DoubleZero // Double Green
        };

          // wheel numbers range from 1-36, as well as, 0 & 00 (#37 & #38, respectively)
        RouletteResult(RouletteColor color, unsigned number) : mColorResult(color), mNumberResult(number) {
          if (mColorResult == RouletteColor::Red)
            mColorResultString = "Red";
          else if (mColorResult == RouletteColor::Black)
            mColorResultString = "Black";
          else if (mColorResult == RouletteColor::Zero) {
            mColorResultString = "Green Zero";
          }
          else if (mColorResult == RouletteColor::DoubleZero) {
            mColorResultString = "Double Green Zero";
          }
        }
        RouletteColor getColor() { return mColorResult; }
        std::string  getColorAsString() { return mColorResultString; }
        unsigned getNumber() { return mNumberResult; }

      private:
        RouletteColor mColorResult;
        std::string mColorResultString;
        unsigned mNumberResult;
    };


    RouletteTable();
    RouletteTable(RouletteTableType wheelType);
    RouletteResult Spin();

  private:
    RouletteTableType mWheelType;
    std::default_random_engine mRandGenerator;
    std::uniform_int_distribution<int> mRandDistribution;
};