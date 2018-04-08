#include "GoL.h"


int main(void) {
  GoL GameOfLife(20, 20, .30);
  GameOfLife.Start();
  
  return 0;
}