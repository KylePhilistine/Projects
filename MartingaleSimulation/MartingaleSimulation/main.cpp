#include "MartingaleSimulator.h"

int main(void) {
  // To play a simplified Roulette simulation uncomment the line below and also comment out the simulation code
  //RouletteController controller = RouletteController(5000, true, true, RouletteTable::RouletteTableType::SingleZeroWheel);

  MartingaleSimulator martingaleSimulator = MartingaleSimulator(20000, 0.0001f, 100000, RouletteTable::RouletteTableType::SingleZeroWheel);
  martingaleSimulator.Start();

  std::cout << std::endl;
  std::cout << "Simulation has finished" << std::endl;
  std::cout << "Press enter to exit" << std::endl;
  std::cin.get();
  return 0;
}