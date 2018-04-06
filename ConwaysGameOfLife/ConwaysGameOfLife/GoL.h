#pragma once

#include <vector>


class GoL {
  public:
    GoL(int boardWidth, int boardHeight, float chanceOfLife);
    void Start();

  private:
    std::vector<std::vector<char>> mBoard;
    int mBoardWidth;
    int mBoardHeight;
    void PrintBoard();  // prints the board in its current state
    void NextGeneration(); // changed the to the next generation of living cells
};