#include <sstream>
#include <algorithm>
#include <ctype.h>

#include "RouletteController.h"


RouletteController::RouletteController(int startingMoney, bool printSpinResults, bool manualControl, RouletteTable::RouletteTableType tableType) : 
  mMoney(startingMoney),
  mPrintSpinResults(printSpinResults),
  mTable(RouletteTable(tableType)),
  mTotalSpins(0)
{
  if(manualControl)
    GoToMainMenu();
}

bool RouletteController::MakeSpin(int bet, RouletteTable::RouletteResult::RouletteColor chosenColor) {
  RouletteTable::RouletteResult result = mTable.Spin();
  bool won = result.getColor() == chosenColor;

  if (mPrintSpinResults) {
    mPrinter.printSpinResult(mTotalSpins, won, mMoney, bet, result);
  }

  if (won) {
    mMoney += bet;
    handleStatisticsLogging(true, bet, result);
  }
  else {
    mMoney -= bet;
    handleStatisticsLogging(false, bet, result);
  }

  return won;
}


// private functions:

void RouletteController::GoToMainMenu() {
  bool displayMenuHeader = true;
  
  while (1) {
    if (displayMenuHeader) {
      std::cout << "Main Menu" << std::endl;
      std::cout << "Enter 1: Place a Bet" << std::endl;
      std::cout << "Enter 2: Add more money" << std::endl;
      std::cout << "Enter 3: Exit" << std::endl << std::endl;
      displayMenuHeader = false;
    }

    std::string userInput;
    std::getline(std::cin, userInput);

    if (userInput == "1") {
      std::cin.clear();
      GoToPlaceBetMenu();
      displayMenuHeader = true;
    }
    if (userInput == "2") {
      std::cin.clear();
      GoToAddMoneyMenu();
      displayMenuHeader = true;
    }
    if (userInput == "3") {
      return;
    }
    std::cin.clear();
  }
}

void RouletteController::GoToPlaceBetMenu() {
  bool displayMenuHeader = true;

  while (1) {
    if (displayMenuHeader) {
      std::cout << "Place A Bet Menu" << std::endl;
      std::cout << "Enter a non-zero amount you would like to bet, or enter exit or back to leave this screen" << std::endl;
      std::cout << "How much would you like to bet?" << std::endl;
      std::cout << "Current Money: " << mMoney << std::endl << std::endl;
      displayMenuHeader = false;
    }
    std::string userInput;
    std::cin >> userInput;


    if (userInput == "back" || userInput == "exit") {
      std::cin.clear();
      return;
    }

    if(isValidNumber(userInput)) {
      int usersBet;
      std::stringstream(userInput) >> usersBet;
      if (usersBet > mMoney) {
        std::cout << "Sorry, you do not have enough money for that bet, input another bet" << std::endl;
      }
      if (usersBet == 0) {
        std::cout << "Sorry, you cannot bet $0, please input a non-zero bet" << std::endl;
      }
      else {
        std::cout << "Enter a color you would like to bet on. (Black or Red)" << std::endl;

        while (displayMenuHeader == false) {
          std::string usersColor;
          std::cin >> usersColor;

          if (usersColor == "back" || usersColor == "exit") {
            std::cin.clear();
            displayMenuHeader = true;
            break;
          }

            // change users input to lower case to check the color properly
          std::transform(usersColor.begin(), usersColor.end(), usersColor.begin(), [](unsigned char c) -> std::size_t { 
              if (c >= 'A' && c <= 'Z')
                return (c + ' ');
              else
                return c;
            }
          );
          
          if (usersColor == "black") {
            MakeSpin(usersBet, RouletteTable::RouletteResult::RouletteColor::Black);
            std::cin.clear();
            displayMenuHeader = true;
            break;
          }
          else if (usersColor == "red") {
            MakeSpin(usersBet, RouletteTable::RouletteResult::RouletteColor::Red);
            std::cin.clear();
            displayMenuHeader = true;
            break;
          }
          else {
            std::cout << "Sorry, the color you entered was invalid, please try again." << std::endl;
          }
        }
      }
    }
    else {
      std::cout << "Sorry, the bet you entered was not a valid number or input, please try again" << std::endl;
    }
  }
}

void RouletteController::GoToAddMoneyMenu() {
  std::cout << "Add Money Menu" << std::endl;
  std::cout << "Enter a non-zero amount you would like to add to your accout, or enter exit or back to leave this screen" << std::endl;
  std::cout << "Current Total: " << mMoney << std::endl;

  while (1) {
    std::string userInput;
    std::cin >> userInput;

    if (userInput == "back" || userInput == "exit") {
      std::cin.clear();
      return;
    }

    if (isValidNumber(userInput)) {
      int addedFunds;
      std::stringstream(userInput) >> addedFunds;

      mMoney += addedFunds;
      std::cout << "Funds added to account" << std::endl;
      std::cout << "New Total: " << mMoney << std::endl << std::endl;
      std::cin.clear();
      return;
    }
    else {
      std::cout << "Sorry, you entered an invalid option/number, please try again" << std::endl;
    }
    std::cin.clear();
  }
}



void RouletteController::handleStatisticsLogging(bool won, int bet, RouletteTable::RouletteResult result) {
  this->mPreviousResults.push_back(result);
  mVariance.push_back(won ? bet : -bet);
  ++mTotalSpins;
}

bool RouletteController::isValidNumber(std::string usersInputStr) {
  if (usersInputStr.empty())
    return false;

  for (unsigned i = 0; i < usersInputStr.size(); ++i) {
    if (usersInputStr[i] < '0' || usersInputStr[i] > '9') {
      return false; // the string is not a number, NaN so in validate the request
    }
  }
  return true;
}