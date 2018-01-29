#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Header file for the rules of tic tac toe
  Name: Boris Skurikhin
  ID: 1007339
  Purpose: To serve and help with the creation of assignment 1.
*/

struct strategy_struct {
  char best_move;
  char winner;
};

#ifndef TICTACTOE_H
#define TICTACTOE_H

/*Functions that are related to the rules of tic tac toe*/

char winner(unsigned short us);

unsigned short next(unsigned short us, char pos);

char get_move(char b3[10]);

char get_turn(char b3[10]);
char get_t(unsigned short us);

/*More general functions*/

unsigned short b3tous(char b3[10]);

void b3fromus(char b3[10], unsigned short us);

void boardtob3(char b3[10], char board[60]);

void boardfromb3(char board[60], char b3[10]);

/* File control functions */

void get_record(FILE *file, unsigned short us, struct strategy_struct *record);

void set_record(FILE *file, unsigned short us, struct strategy_struct record);

void evalMove(struct strategy_struct *stratStract, unsigned short board, FILE* fp);

#endif
