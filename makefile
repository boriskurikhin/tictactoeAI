all: a1p1 a1p2 a1p3 a1p4 a1p5

a1p1: a1p1.c tictactoe.o tictactoe.h
	gcc -Wall -ansi -pedantic a1p1.c tictactoe.o -o a1p1

a1p2: a1p2.c tictactoe.o tictactoe.h
	gcc -Wall -ansi -pedantic a1p2.c tictactoe.o -o a1p2

a1p3: a1p3.c tictactoe.o tictactoe.h
	gcc -Wall -ansi -pedantic a1p3.c tictactoe.o -o a1p3

a1p4: a1p4.c tictactoe.o tictactoe.h
	gcc -Wall -ansi -pedantic a1p4.c tictactoe.o -o a1p4

a1p5: a1p5.c tictactoe.o tictactoe.h
	gcc -Wall -ansi -pedantic a1p5.c tictactoe.o -o a1p5

tictactoe.o: tictactoe.c tictactoe.h
	gcc -Wall -ansi -pedantic -c tictactoe.c -o tictactoe.o
