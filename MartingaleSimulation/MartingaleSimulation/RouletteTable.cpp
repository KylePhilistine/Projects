#include "RouletteTable.h"

RouletteTable::RouletteTable() {
  mWheelType = RouletteTableType::SingleZeroWheel;
  // set up the ranges of the table, 37 slots for a single zero wheel, 38 for a double zero wheel
  this->mRandDistribution = std::uniform_int_distribution<int>(1, mWheelType == RouletteTableType::SingleZeroWheel ? 37 : 38);
  this->mRandGenerator = std::default_random_engine(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
}

RouletteTable::RouletteTable(RouletteTableType wheelType) : mWheelType(wheelType) {
    // set up the ranges of the table, 37 slots for a single zero wheel, 38 for a double zero wheel
  this->mRandDistribution = std::uniform_int_distribution<int>(1, wheelType == RouletteTableType::SingleZeroWheel ? 37 : 38);
  this->mRandGenerator = std::default_random_engine(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
}



RouletteTable::RouletteResult::RouletteColor DetermineNumbersColor(unsigned int number) {
  bool isEven = (number % 2) == 0;
  bool blackRedRange = false; // black-red range refers to odd numbers being black and evens being red. red-black range would be the opposite

    // Color Ranges: 1-10 & 19-28 (odd == red && even == black), 11-18 & 29-36 (odd == black && even == red)
  if (number <= 10) {
    blackRedRange = false;
  }
  else if (number >= 19 && number <= 28) {
    blackRedRange = false;
  }
  else if (number >= 11 && number <= 18) {
    blackRedRange = true;
  }
  else if (number >= 29 && number <= 36) {
    blackRedRange = true;
  }
  else if (number == 37) { // green zero
    return RouletteTable::RouletteResult::RouletteColor::Zero;
  }
  else if (number == 38) { // double green zero
    return RouletteTable::RouletteResult::RouletteColor::Zero;
  }

  RouletteTable::RouletteResult::RouletteColor color;

  if (isEven) {
    if (blackRedRange) {
      color = RouletteTable::RouletteResult::RouletteColor::Red;
    }
    else {
      color = RouletteTable::RouletteResult::RouletteColor::Black;
    }
  }
  else { // number is odd
    if (blackRedRange) {
      color = RouletteTable::RouletteResult::RouletteColor::Black;
    }
    else {
      color = RouletteTable::RouletteResult::RouletteColor::Red;
    }
  }

  return color;
}

RouletteTable::RouletteResult RouletteTable::Spin() {
  int result = mRandDistribution(this->mRandGenerator);
  return RouletteResult(DetermineNumbersColor(result), result);
}