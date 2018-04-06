#include <assert.h> // error handling for board size
#include <iostream> // debugging
#include <random>   // random engine for placing cells
#include <chrono>   // seeding the random engine for true randomness

#include "GoL.h"

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
      this->mBoard[row][column] = distribution(generator) ? 254 : ' ';
    }
  }

  this->PrintBoard();
}

void GoL::Start() {
  while (1) {
    this->NextGeneration();
    this->PrintBoard();
  }
}


  // private functions:

void GoL::PrintBoard() {
  system("cls"); // remove everything from the console and start fresh

    // loops through the board row major and prints it to the console
  for (int row = 0; row < this->mBoardHeight; ++row) {
      // adds a dashed line to separate each row of cells
    for (int i = 0; i < this->mBoardWidth; ++i) {
      if (i == 0) {
        std::cout << "  -";
      }
      else {
        std::cout << "   -";
      }
    }
    std::cout << std::endl;

      // shows the living cells and the dividers between each cell
    for (int column = 0; column < this->mBoardWidth; ++column) {
      if (column == 0) {
        std::cout << "| ";
      }
      std::cout << this->mBoard[row][column] << " | ";
    }
    std::cout << std::endl;
  }

    // adds the last row of dashes to the board on the console
  for (int i = 0; i < this->mBoardWidth; ++i) {
    if (i == 0) {
      std::cout << "  -";
    }
    else {
      std::cout << "   -";
    }
  }

  std::cout << std::endl;
}



int getNeighborCount(int cellRow, int cellColumn) {
  return 0;
}

char predictNextGeneration(int cellRow, int cellColumn) {
  int neighbors = getNeighborCount(cellRow, cellColumn);

    // Rule 1: Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
  if (neighbors < 2) {
    return ' ';
  }

    // Rule 2: Any live cell with two or three live neighbours lives on to the next generation.
    // Rule 4: Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
  if (neighbors == 2 || neighbors == 3) {
    return 254; // ascii character for a square
  }

    // Rule 3: Any live cell with more than three live neighbours dies, as if by overpopulation.
  return ' ';
}

void GoL::NextGeneration() {
  std::vector<std::vector<char>> nextGeneration;


  nextGeneration.resize(this->mBoardHeight);
  for (int i = 0; i < this->mBoardHeight; ++i) {
    nextGeneration[i].resize(this->mBoardWidth);
  }
  
  for (int row = 0; row < this->mBoardHeight; ++row) {
    for (int column = 0; column < this->mBoardWidth; ++column) {
      nextGeneration[row][column] = predictNextGeneration(row, column);
    }
  }
  this->mBoard = nextGeneration;
}