#pragma once
#include "RouletteTable.h"

  // this class is responsible for controlling the programs flow, taking the users
  // input and running the underlying code(this is essentially the Front End).
class RouletteTableController
{
  public:
    RouletteTableController();
    ~RouletteTableController();
    void Start();

  private:
    void Run();

    // Display Messages
    void DisplayProgramHeader();
    void DisplayHelpOptions();

    // private variables
    RouletteTable* mRouletteTable;
};