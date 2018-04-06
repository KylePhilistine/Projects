#include "Fizzbuzz.h"
#include <string>

void Fizzbuzz(int start, int end) {
  if (start > end) {
    std::cout << "Error: start was greater than the end" << std::endl;
    return;
  }

  for (int i = start; i <= end; ++i) {
    std::string output = "";
    if (i % 3 == 0) {
      output += "Fizz";
    }
    if (i % 5 == 0) {
      output += "Buzz";
    }

    if (output.empty()) {
      std::cout << i;
    }
    else {
      std::cout << output;
    }

    std::cout << std::endl;
  }
}