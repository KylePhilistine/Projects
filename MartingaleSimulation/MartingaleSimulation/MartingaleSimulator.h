#pragma once

#include "RouletteController.h"

class MartingaleSimulator {
  public:
    // int startingAmount : this is how much money you want the simulation to start with
    // float bettingPercent : this will determine how much money your starting bet should be
    // int stopAfterXMoneyMade : this value pertains to how much money you want to make before stopping the simulation
    // RouletteTableType tableType : this determines what type of table the simulation will use. Single Zero Table (37 spots) or Double Zero Table (38 spot)
    MartingaleSimulator(int startingAmount, float bettingPercent, int stopAfterXMoneyMade, RouletteTable::RouletteTableType tableType);

    void Start();

  private:
    RouletteController mController;
    float mBettingPercent;
    int mStoppingAmount;

};