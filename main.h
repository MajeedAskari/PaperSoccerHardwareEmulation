#ifndef MAIN_H_
#define MAIN_H_

#define row 13
#define col 9

#include <stdio.h>

enum States
{
    start,
    oppTurn,
    ourTurn,
    findingMove,
    moveTransfer
};

struct node
{
    char move;
};

enum States currentState, nextState;
unsigned char map[row][col];
int currentStack, doneStack;
int ballX, ballY;

void printMap(void);

#endif