# TicTacToe AI

This program was developed for a computer science assignment. It's a simple AI for a single-player tictactoe game. 
It develops a binary file consisting of bits representing possible strategies for all possible/non-possible boards in the game. 

The program contains 8 important files, the rest are either excecutables or debug stuff.

1. makefile
  * Helps us create excecutables and compile all our programs with _-Wall -ansi -pedantic_ tags
2. tictactoe.h
  * Contains all function definitions
3. tictactoe.c
  * Contains all functions, including a very important function tied closely with our AI _evalMove_
  ```c
  void evalMove(struct strategy_struct *record, unsigned short board, FILE* fp) {
	unsigned short nextBoard;
	char result;
	struct strategy_struct nextRecord;
	int i, tiePos, foundTie = 0, legalMove = 0;
	/* loop through 9 possible boards */
	for(i = 0; i <= 8; i++) {
		nextBoard = next(board, i);
		if (nextBoard != 0) {
			get_record(fp, nextBoard, &nextRecord);
			result = nextRecord.winner;
			/* if there exists a winning board */
			if (result == (get_t(board) + '0')){
				(*record).winner = result;
				(*record).best_move = i;
				return; /* escape */
			}
			if (result == '0' && !foundTie) {
				foundTie = 1;
				tiePos = i;
			} else {
				legalMove = i;
			}
		}
	}
	/* if we found a tie */
	if (foundTie == 1) {
		(*record).winner = '0';
		(*record).best_move = tiePos;
	} else {
		(*record).best_move = legalMove;
		if (get_t(board) == 2) {
			(*record).winner = '1';
		} else {
			(*record).winner = '2';
		}
	}
}
```
  
  
