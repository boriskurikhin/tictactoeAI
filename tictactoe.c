#include "tictactoe.h"

/*
	Boris Skurikhin
	1007339
	A1 - tictactoe.c
*/

char winner(unsigned short us){
	/*win.rar*/
	/*
		0 1 2
		3 4 5
		6 7 8
	*/
	char board[10] = "000000000", win = ' ';
	b3fromus(board, us);
	/*return 2 for X, 1 for O, 0 for tie, ' ' for no one
	if this was c++ we could have used substr*/
	if (us == 0)
		return '0';

	if (board[4] != '0') {
		if (board[2] == board[4] && board[6] == board[4]) {
			/*diagonal 1*/
			win = board[4];
		} else if (board[0]	== board[4] && board[8] == board[4]) {
			/*diagonal 2*/
			win = board[4];
		} else if (board[1] == board[4] && board[7] == board[4]) {
			/*mid-column*/
			win = board[4];
		} else if (board[3] == board[4] && board[5] == board[4]) {
			/*mid-row*/
			win = board[4];
		}
  }

  	if (board[0] != '0') {
  		if (board[0] == board[1] && board[0] == board[2]) {
  			/*top-row*/
  			win = board[0];
  		} else if (board[0] == board[3] && board[6] == board[0]) {
  			/*left-col*/
  			win = board[0];
  		}
  	}

    if (board[8] != '0') {
  		if (board[8] == board[7] && board[8] == board[6]) {
  			/*bot-row*/
  			win = board[8];
  		} else if (board[8] == board[2] && board[8] == board[5]) {
  			/*right-col*/
  			win = board[8];
  		}
  	}
		/* tie */
		if (get_move(board) == 9 && win == ' ')
			return '0';
  	/*returns ' ' if there is no winner!*/
  	return win;
}

unsigned short next(unsigned short us, char pos) {
	char board[10] = "000000000";
	b3fromus(board, us);
	/*if a piece already exists in that location, return 0*/
	if (board[(int)pos] != '0')
		return 0;
	/*otherwise set location*/
	board[(int)pos] = (char)(get_turn(board) + '0');
	return b3tous(board);
}

char get_move(char b3[10]) {
	int counter = 0, i = 0;
	for (i = 0; i < 9; i++) {
		/*conditional if statement*/
		counter += b3[i] == '0' ? 0 : 1;
	}
	/* printf("GET MOVE RETURNED %d\n", counter); */
	return counter;
}

char get_turn(char b3[10]) {
	int numMoves = get_move(b3);
	if (numMoves % 2 == 0) {
		return 2;
	} else {
		return 1;
	}
}

char get_t(unsigned short us) {
	char temp[10] = "000000000";
	b3fromus(temp, us);
	return get_turn(temp);
}

/*Trinary functions*/

unsigned short b3tous(char b3[10]) {
	unsigned short result = 0;
	int i, multi = 1;
	/*We start at 8 because 9th index is the /0!*/
	for (i = 8; i >= 0; i--) {
		result += (b3[i] - '0') * multi;
		multi *= 3;
	}
	return result;
}

void b3fromus(char b3[10], unsigned short us) {
	int index = 0;
	while (us >= 1){
		/*adding a '0' converts an integer to a character
		we take mod becuase converting to any base, you take the
		mod of that base.*/
		b3[(8 - index)] = (char)(us % 3 + '0');
		/*since numbers read from right-to left, we offset by index*/
		index++;
		us /= 3;
	}
		b3[9] = '\0';
}

void boardtob3(char b3[10], char board[60]) {
	int i = 0, index = 0;
	/*Domain: 1 thru 57
		in order to not get out-of-bounds exception when checking previous and next characters
		also not to 58, because the last character is /0 and it's not a part of the board.*/
	for (i = 1; i < 58; i++) {
		if (board[i] == 'X' || board[i] == 'O' || board[i] == ' ') {
			/*makes sure that the important character is surrounded by spaces*/
			if (board[i - 1] == ' ' && board[i + 1] == ' ') {
				switch (board[i]) {
					case 'X':
						b3[index] = '2';
						break;
					case 'O':
						b3[index] = '1';
						break;
					default:
						b3[index] = '0';
				}
				/*we need this to fill out the string array*/
				index++;
			}
		}
	}
	b3[9] = '\0';
}

void boardfromb3(char board[60], char b3[10]) {
	int i = 0, j = 0;
	strcpy(board, " ? | ? | ? \n---+---+---\n ? | ? | ? \n---+---+---\n ? | ? | ? ");
	/*question marks represent possible player positions or empty spaces*/
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 59; j++) {
			if (board[j] == '?') {
				switch(b3[i]){
					case '2':
						board[j] = 'X';
						break;
					case '1':
						board[j] = 'O';
						break;
					default:
						board[j] = ' ';
				}
				/*if we found an empty cell, we replace it, and keep going.
				if we don't break it will repalce all cells with first value*/
				break;
			}
		}
	}
}

void get_record(FILE *file, unsigned short us, struct strategy_struct *record) {
	/* reads record from our binary file */
	fseek(file, sizeof(struct strategy_struct) * us, SEEK_SET);
	fread(record, sizeof(struct strategy_struct), 1, file);
}

void set_record(FILE *file, unsigned short us, struct strategy_struct record) {
	/* writes record to our binary file */
	fseek(file, sizeof(struct strategy_struct) * us, SEEK_SET);
	fwrite(&record, sizeof(struct strategy_struct), 1, file);
}

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
