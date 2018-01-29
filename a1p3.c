#include "tictactoe.h"

/*
	Boris Skurikhin
	1007339
	A1 - P3
*/

int main(int argc, char *argv[]){

  FILE* fp;
  int moves[10];
  char tempb3[10];
  int i;
  unsigned short _board = 0;
  struct strategy_struct tempStrat;

/*  write(); */ /* write all empty values */
  fp = fopen("strategy.bin", "rb+");

  if (argc != 2) {
    printf("Improper amount of arguments supplied...");
    exit(1);
  }
   /*It the assignment it said the command argument should be
     set to -> 9,8,7,6,5,4,3,2,1,0. Thus, I read in all the move
     numbers in one single command argument.
   */
    sscanf(argv[1], "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &moves[0], &moves[1], &moves[2], &moves[3], &moves[4], &moves[5], &moves[6], &moves[7], &moves[8], &moves[9]);

  for (i = 0; i <= 9; i++) {
    /* i represents move number */
    for (_board = 0; _board < 19683; _board++) {

      strcpy(tempb3, "000000000");
      b3fromus(tempb3, _board);

      if (moves[i] == get_move(tempb3)) {

        if (winner(_board) != ' ') {
	  /* defaults to  the middle, since it's the best init. position */
          tempStrat.winner =  winner(_board);
          tempStrat.best_move = (_board == 0 ? 0 : -1);
          set_record(fp, _board, tempStrat);

        } else {
          /* basically, if it's our turn right now, we know that next turn is not ours.
            however, the turn after is...we need to sort of look ahead two steps. */
            evalMove(&tempStrat, _board, fp);
            set_record(fp, _board, tempStrat);
          }
        }
      }
    }

  fclose(fp);
  return 0;
}
