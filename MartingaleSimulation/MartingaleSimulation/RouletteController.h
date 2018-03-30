#pragma once

#include <vector>
#include <iostream>

#include "RouletteTable.h"

class RouletteController{

  class RoulettePrinter {
    public:
      RoulettePrinter() {}
      void printSpinResult(int totalSpins, bool won, int totalMoney, int bet, RouletteTable::RouletteResult spinResult) {
        std::cout << "Spin #" << totalSpins << ": " << spinResult.getColorAsString() << " " << spinResult.getNumber() << std::endl;
        if (bet > 0) {
          std::cout << (won ? "won: " : "lost: ") << bet << " " << "total: " << (won ? totalMoney + bet : totalMoney - bet) << std::endl << std::endl;
        }
      }
    private:
  };

  public:
    RouletteController(int startingMoney, bool printSpinResults, bool manualControl, RouletteTable::RouletteTableType tableType);

    bool MakeSpin(int bet, RouletteTable::RouletteResult::RouletteColor chosenColor);
    int getMoney() { return mMoney; }
    int getTotalSpins() { return mTotalSpins; }

  private:
    int mMoney;
    bool mPrintSpinResults = false;
    RouletteTable mTable;
    RoulettePrinter mPrinter;

      // statistics 
    unsigned int mTotalSpins;
    std::vector<RouletteTable::RouletteResult> mPreviousResults;
    std::vector<int> mVariance; // tracks gains/loses per spin (['SpinNumber'] = 'SpinResult')


    void GoToMainMenu();
    void GoToPlaceBetMenu();
    void GoToAddMoneyMenu();
    void handleStatisticsLogging(bool won, int bet, RouletteTable::RouletteResult result);
    bool isValidNumber(std::string);
};