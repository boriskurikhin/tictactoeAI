#include "tictactoe.h"

/*
	Boris Skurikhin
	1007339
	A1 - P1
*/

int main(int argc, char *argv[]) {

	unsigned short boardNum;
	char boardb3[10] = "000000000", board[60] = "";
	int move, turn, win, i;

	if (argc != 2) {
	    printf("Improper amount of arguments supplied...");
   	    exit(1);
  	}

	printf("Board number: ");
	sscanf(argv[1], "%hu", &boardNum);

	/*Setting up & retrieving values*/

	b3fromus(boardb3, boardNum);
	boardfromb3(board, boardb3);
	move = get_move(boardb3);
	turn = get_turn(boardb3);
	win = winner(boardNum);

	/*All print statements*/

	printf("Board b3: %s\n", boardb3);
	printf("Board pic: \n%s\n", board);
	printf("Move: %d\n", move);
	printf("Turn: %d\n", turn);
	printf("Winner: %c\n", win);

	for (i = 0; i < 9; i++)
	    printf("%d -> %hu\n", i, next(boardNum, i));

	return 0;
}
