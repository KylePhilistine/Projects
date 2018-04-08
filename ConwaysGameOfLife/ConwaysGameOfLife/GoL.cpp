#include <assert.h> // error handling for board size
#include <iostream> // debugging
#include <random>   // random engine for placing cells
#include <chrono>   // seeding the random engine for true randomness

#include "GoL.h"
#include "Timer.h"

  // Defines for clarity between living vs. dead cells
#define ALIVE_CELL 254
#define DEAD_CELL ' '


GoL::GoL(int boardWidth, int boardHeight, float chanceOfLife) {
  assert(!(boardWidth == 0 || boardWidth == 0));
  assert(chanceOfLife <= 1);
  this->mBoardWidth = boardWidth;
  this->mBoardHeight = boardHeight;

    // initialize the height and width of the board
  this->mBoard.resize(boardHeight);
  for (int i = 0; i < boardHeight; ++i) {
    this->mBoard[i].resize(boardWidth);
  }
   
    // create the seeded random generator & distribution model to randomly place cells on the board
  std::bernoulli_distribution distribution(chanceOfLife);
  std::default_random_engine generator(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
  
    // randomly place living cells on the board
  for (int row = 0; row < boardHeight; ++row) {
    for (int column = 0; column < boardWidth; ++column) {
      this->mBoard[row][column] = Cell(distribution(generator) ? ALIVE_CELL : DEAD_CELL);
    }
  }

  this->PrintBoard();
}



void GoL::Start() {
  Timer timer(.05);
  timer.Start();
  while (1) {
    if (timer.HasFinished()) {
      this->NextGeneration();
      timer.Reset();
      timer.Start();
    }
  }
}


  // GoL private functions:
void GoL::PrintBoard() {
  system("cls"); // remove everything from the console and start fresh

    // loops through the board row major and prints it to the console
  for (int row = 0; row < this->mBoardHeight; ++row) {
      // shows the living cells and the dividers between each cell
    for (int column = 0; column < this->mBoardWidth; ++column) {
      std::cout << this->mBoard[row][column].getCell() << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}



std::vector<GoL::Cell> getNeighbors(int cellRow, int cellColumn, const std::vector<std::vector<GoL::Cell>>& board) {
  std::vector<GoL::Cell> neighbors;
  int boardWidth = board[0].size();
  int boardHeight = board.size();

    // top left corner check
  if (cellRow - 1 >= 0 && cellColumn - 1 >= 0) {
    neighbors.push_back(board[cellRow - 1][cellColumn - 1]);
  }

    // top middle check
  if (cellRow - 1 >= 0) {
    neighbors.push_back(board[cellRow - 1][cellColumn]);
  }

    // top right check
  if (cellRow - 1 >= 0 && cellColumn + 1 < boardWidth) {
    neighbors.push_back(board[cellRow - 1][cellColumn + 1]);
  }

    // middle right check
  if (cellColumn + 1 < boardWidth) {
    neighbors.push_back(board[cellRow][cellColumn + 1]);
  }

    // bottom right check
  if (cellRow + 1 < boardHeight && cellColumn + 1 < boardWidth) {
    neighbors.push_back(board[cellRow + 1][cellColumn + 1]);
  }

    // bottom middle check
  if (cellRow + 1 < boardHeight) {
    neighbors.push_back(board[cellRow + 1][cellColumn]);
  }

    // bottom left check
  if (cellRow + 1 < boardHeight && cellColumn - 1 >= 0) {
    neighbors.push_back(board[cellRow + 1][cellColumn - 1]);
  }

  // middle left check
  if (cellColumn - 1 >= 0) {
    neighbors.push_back(board[cellRow][cellColumn - 1]);
  }

  return neighbors;
}



char predictNextGeneration(int cellRow, int cellColumn, const std::vector<std::vector<GoL::Cell>>& board) {
  std::vector<GoL::Cell> neighbors = getNeighbors(cellRow, cellColumn, board);
  int aliveNeighbors = 0;

  for (int i = 0; i < neighbors.size(); ++i) {
    if (neighbors[i].isAlive()) {
      ++aliveNeighbors;
    }
  }

    // Rule 1: Any live cell with fewer than two live neighbors dies, as if caused by underpopulation.
  if (aliveNeighbors < 2) {
    return DEAD_CELL;
  }

    // Rule 2: Any live cell with two or three live neighbors lives on to the next generation.
  if (board[cellRow][cellColumn].isAlive() && (aliveNeighbors == 2 || aliveNeighbors == 3)) {
    return ALIVE_CELL; // ascii character for a square
  }

    // Rule 4: Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
  if (!board[cellRow][cellColumn].isAlive() && aliveNeighbors == 3) {
    return ALIVE_CELL;
  }

    // Rule 3: Any live cell with more than three live neighbors dies, as if by overpopulation.
  return DEAD_CELL;
}



void GoL::NextGeneration() {
  std::vector<std::vector<Cell>> nextGeneration;

  nextGeneration.resize(this->mBoardHeight);
  for (int i = 0; i < this->mBoardHeight; ++i) {
    nextGeneration[i].resize(this->mBoardWidth);
  }
  
  for (int row = 0; row < this->mBoardHeight; ++row) {
    for (int column = 0; column < this->mBoardWidth; ++column) {
      nextGeneration[row][column] = Cell(predictNextGeneration(row, column, this->mBoard));
    }
  }
  this->mBoard = nextGeneration;
  this->PrintBoard();
}



// Cell Class Definitions:
GoL::Cell::Cell() {
  mCellStatus = DEAD_CELL;
}



GoL::Cell::Cell(char cellStatus) : mCellStatus(cellStatus) {

}