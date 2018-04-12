#include "tictactoe.h"

int main(){
  char name[41] = "", boardPic[60], b3[10] = "000000000";
  int turn = 1, pos = 0, i, instawin = 0;
  unsigned short board = 0, nextBoard;
  char piece1, piece2;
  struct strategy_struct myStrategy;
  FILE* fp;
  fp = fopen("strategy.bin", "rb");

  printf("SHALL WE PLAY A GAME?\n\n");
  printf("PLEASE ENTER YOUR NAME:  ");
  fgets(name, 40, stdin);
  name[strlen(name)-1] = '\0';
  printf("\nGREETINGS %s", name);
  printf("\nWhich side would you like to play (X/O)?  ");
  scanf("%c", &piece1);
  if (piece1 == 'O') {
    piece2 = 'X';
    turn = 1;
  }
  else if (piece1 == 'X') {
    piece2 = 'O';
    turn = 0;
  }
  else {
    /* we wanna make sure the user chooses the right piece */
    printf("Invalid choice!");
    return 0;
  }
  printf("Ok, you will be %c; I will be %c.", piece1, piece2);
  b3fromus(b3, board);
  boardfromb3(boardPic, b3);
  printf("\n\n%s", boardPic);

  while (get_move(b3) < 9) {
    if (board > 0 && winner(board) != ' ') {
      break;
    }
    if (turn) {
      printf("\n\nMy turn; my move is");
      get_record(fp, board, &myStrategy);
      instawin = 0;

	  /* if there's a win on the board it will go there, regardless */

	  for (i = 0; i < 9; i++) {
		  nextBoard = next(board, i);
		  if (nextBoard && winner(nextBoard) != ' ' && winner(nextBoard) != '0') {
			  printf(" %d:", i);
			  instawin = 1;
			  break;
		  }
	  }
 	  /* if there's no instant winning move */
	  if (!instawin) {
	      printf(" %d:", myStrategy.best_move);
	      nextBoard = next(board, myStrategy.best_move);
	  }
    } else {
          redo:
      printf("\n\nYour turn; chose a move [0-8]: ");
      scanf("%d", &pos);
      nextBoard = next(board, pos);
	  /* if the player inputs an illegal move */
	  if (!nextBoard){
		  nextBoard = board;
		  printf("\nInvalid move!");
		  /* jumps back to move selection, assembly command */
		  goto redo;
	  }
    }
	board = nextBoard;
	turn ^= 1; /* flip turn */
	b3fromus(b3, board);
   	boardfromb3(boardPic, b3);
   	printf("\n\n%s", boardPic);
  }

  get_record(fp, board, &myStrategy);
  if (myStrategy.winner == piece1) {
	  /* Shouldn't happen, like ever */
   	 printf("\n\nI lost!\n\nLET'S PLAY AGAIN!\n\n");
  } else if (myStrategy.winner == '0') {
   	 printf("\n\nThe game is a tie.\n\nA STRANGE GAME.\nTHE ONLY WINNING MOVE IS\nNOT TO PLAY.\n\n");
  } else {
   	 printf("\n\nI won!\n\nA STRANGE GAME.\nTHE ONLY WINNING MOVE IS\nNOT TO PLAY.\n\n");
  }
  fclose(fp);
  return 0;
}
