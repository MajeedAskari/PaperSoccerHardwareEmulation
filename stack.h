#ifndef STACK_H_

#define STACK_H_
#include "main.h"
#include <stdlib.h>

#define STACK_TYPE int
#define NUMBER_OF_STACKS 10
#define MAX_NUMBER_OF_ELEMENTS 10 * row *col

int sInit(int stackSize);
void sPush(STACK_TYPE data, int stackID);
STACK_TYPE sPop(int stackID);

#endif