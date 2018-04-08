#pragma once

#include <vector>


class GoL {
  public:
    GoL(int boardWidth, int boardHeight, float chanceOfLife);
    void Start();

    class Cell {
      public:
        Cell();
        Cell(char cellStatus);

        char getCell() const { return mCellStatus; }
        bool isAlive() const { return mCellStatus == ' ' ? false : true; }

      private:
        char mCellStatus; // char 254 (square) = living, space (' ') = dead
    };



  private:
    std::vector<std::vector<Cell>> mBoard;
    int mBoardWidth;
    int mBoardHeight;
    void PrintBoard();  // prints the board in its current state
    void NextGeneration(); // changed the to the next generation of living cells
};