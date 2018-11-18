#ifndef STACK_H_
#define STACK_H_

#include "main.h"
#include <stdlib.h>
#include <stdio.h>

#define STACK_TYPE struct node
#define NUMBER_OF_STACKS 10
#define MAX_NUMBER_OF_ELEMENTS 10 * row *col

int sInit(int stackSize);
void sPush(STACK_TYPE data, int stackID);
STACK_TYPE sPop(int stackID);
STACK_TYPE sPeek(int stackID);
void sPrintStack(int stackID);
int sSize(int stackID);
void sCopyStack(int source, int dest);
STACK_TYPE sGet(int stackID, int index);


#endif