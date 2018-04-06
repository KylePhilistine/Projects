#include "GoL.h"


int main(void) {
  GoL GameOfLife(10, 10, .30);
  GameOfLife.Start();
  
  return 0;
}