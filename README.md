# TicTacToe AI

This program was developed for a computer science assignment. It's a simple AI for a single-player tictactoe game. 
It develops a binary file consisting of bits representing possible strategies for all possible/non-possible boards in the game. 

The program contains 8 important files, the rest are either excecutables or debug stuff.

**makefile** - helps us create excecutables and compile all our programs with _-Wall -ansi -pedantic_ tags
**tictactoe.h** - contains all function definitions
**tictactoe.c** - contains all functions, including a very important function tied closely with our AI _evalMove_
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
**a1p1.c** - this program is just a checker to ensure all functions work
**a1p2.c** - populates the binary file with default data
```c
struct strategy_struct {
  char best_move;
  char winner;
};
```
**a1p3.c** - a very important program that populates and creates our AI using _evalMove_, which I linked above.
**a1p4.c** - similar to **a1p1.c**, this program just ensures that **a1.p3** is working correctly.
**a1p5.c** - last program; interactive game.

Sample Game:
```
SHALL WE PLAY A GAME?

PLEASE ENTER YOUR NAME: Boris
GREETINGS Boris

Which side would you like to play (X/O)? O

Ok, you will be O; I will be X.

   |   |   
---+---+---
   |   |   
---+---+---
   |   |   

My turn; my move is 0:

 X |   |   
---+---+---
   |   |   
---+---+---
   |   |   

Your turn; chose a move [0-8]:0

Invalid move!

Your turn; chose a move [0-8]:1


 X | O |   
---+---+---
   |   |   
---+---+---
   |   |   

My turn; my move is 3:

 X | O |   
---+---+---
 X |   |   
---+---+---
   |   |   

Your turn; chose a move [0-8]:6


 X | O |   
---+---+---
 X |   |   
---+---+---
 O |   |   

My turn; my move is 4:

 X | O |   
---+---+---
 X | X |   
---+---+---
 O |   |   

Your turn; chose a move [0-8]:8


 X | O |   
---+---+---
 X | X |   
---+---+---
 O |   | O 

My turn; my move is 5:

 X | O |   
---+---+---
 X | X | X 
---+---+---
 O |   | O 

I won!

A STRANGE GAME.
THE ONLY WINNING MOVE IS
```
