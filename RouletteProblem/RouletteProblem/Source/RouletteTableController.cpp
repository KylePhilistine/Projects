#include "RouletteTableController.h"
#include <iostream>
#include <string>
#include <locale> //tolower


RouletteTableController::RouletteTableController()
{
  mRouletteTable = new RouletteTable();
}

RouletteTableController::~RouletteTableController()
{
  delete mRouletteTable;
}

void RouletteTableController::Start()
{
  this->DisplayProgramHeader();
  Run();
}

// private functions

void RouletteTableController::Run()
{
  this->DisplayHelpOptions();
  while (1)
  {
    std::locale userInputRefPtr;
    std::string userInput = "some";
    std::getline(std::cin, userInput);

    for(unsigned i = 0; i < userInput.size(); ++i)
      userInput[i] = std::tolower(userInput[i], userInputRefPtr);

    if (userInput == "1")
      std::cout << this->mRouletteTable->Spin();
    else if (userInput == "help")
      this->DisplayHelpOptions();
    else
      std::cout << "Input was invalid. If you need the options again enter 'help'" << std::endl;

    userInput = "";
  }
}

void RouletteTableController::DisplayProgramHeader()
{
  std::cout << "***Martingale Betting System***" << std::endl << std::endl;
}

void RouletteTableController::DisplayHelpOptions()
{
  std::cout << "Help Menu" << std::endl;
  std::cout << "  Enter 1: Spin once" << std::endl;
  std::cout << "  Enter 2: " << std::endl;
  std::cout << "  Enter 3: " << std::endl;
}
