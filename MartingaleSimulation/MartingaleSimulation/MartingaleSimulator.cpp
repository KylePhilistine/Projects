#include "MartingaleSimulator.h"

MartingaleSimulator::MartingaleSimulator(int startingAmount, float bettingPercent, int stopAfterXMoneyMade, RouletteTable::RouletteTableType tableType) :
  mController(RouletteController(startingAmount, true, false, tableType)),
  mBettingPercent(bettingPercent),
  mStoppingAmount(stopAfterXMoneyMade)
{

}

void MartingaleSimulator::Start() {
  int consecutiveLoses = 0;
  int moneyGained = 0;
  int startingBet = mController.getMoney()*mBettingPercent;

  std::uniform_int_distribution<int> randDistribution = std::uniform_int_distribution<int>(0, 1);
  std::default_random_engine randGenerator = std::default_random_engine(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
  
  while (moneyGained < mStoppingAmount || mController.getMoney() == 0) {
      // this calculation makes sure that you will always net money after a lose
      // EX: startingAmount = $5,000 | bettingPercent = 0.001% | startingMoney = 5000*0.001 = $5
      // First Spin: You bet $5 & lose the spin | Money = 4995
      // Second Spin: You now bet (2^1) * startingBet = $10 & lose the spin | Money = 4985
      // Third Spin: You now bet (2^2) * startingBet = $20 & lose the spin | Money = 4965
      // Fourth Spin: You now bet (2^3) * startingBet = $40 & win the spin | Money = 5005
      // This will guarantee that you always bet the correct amount to get your original bet back
    int bet = std::pow(2, consecutiveLoses) * startingBet;

    if (bet > mController.getMoney()) {
      std::cout << "Ran out of Money!" << std::endl;
      return;
    }

      // randomly choose a color (Red 0, Black 1)
    RouletteTable::RouletteResult::RouletteColor bettingColor = RouletteTable::RouletteResult::RouletteColor::Black;//(RouletteTable::RouletteResult::RouletteColor)randDistribution(randGenerator);

    bool won = mController.MakeSpin(bet, bettingColor);
    if (won) {
      moneyGained += startingBet; // keep track of how much you've won
      startingBet = mController.getMoney()*mBettingPercent; // calculate the new starting bet since you won
      consecutiveLoses = 0; // reset the lose counter since you won
    }
    else {
      ++consecutiveLoses;
    }
  }
  int stop = 0;
}