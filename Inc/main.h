#ifndef MAIN_H_
#define MAIN_H_

#define row 13
#define col 9
#define clockPeriod 1 // in ms
#define turnPeriod 1000 // in ms

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

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
    int move;
    int value;
    bool finalMove = true;
};

enum States currentState, nextState;
unsigned char map[row][col];
int currentStack, doneStack;
int ballX, ballY;
bool upSide;
long long clock;
HANDLE gDoneEvent;

void printMap(void);
void test(void);

#endif
