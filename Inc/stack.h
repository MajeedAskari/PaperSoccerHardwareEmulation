#ifndef STACK_H_
#define STACK_H_

#include "main.h"
#include <stdlib.h>
#include <stdio.h>

#define STACK_TYPE struct node
#define NUMBER_OF_STACKS 10
#define MAX_NUMBER_OF_ELEMENTS 10 * row *col

void sCopyStack(int source, int dest);
void sClear(int stackID);
void sPrintStack(int stackID);
void sPush(STACK_TYPE data, int stackID);

int sSize(int stackID);
int sInit(int stackSize);

STACK_TYPE sPop(int stackID);
STACK_TYPE sPeek(int stackID);
STACK_TYPE sGet(int stackID, int index);

#endif