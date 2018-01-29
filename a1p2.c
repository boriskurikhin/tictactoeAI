#include "tictactoe.h"

/*
	Boris Skurikhin
	1007339
	A1 - P2
*/

int main(){

  struct strategy_struct strategy;
  FILE *file;
  int i;

  strategy.best_move = -1;
  strategy.winner = ' ';

  file = fopen("strategy.bin", "wb");

  for (i = 0; i < 19683; i++)
    fwrite(&strategy, sizeof(struct strategy_struct), 1, file);

  fclose(file);
  return 0;
}
