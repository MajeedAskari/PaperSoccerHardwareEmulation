#ifndef AI_H_
#define AI_H_

#define MAX_DEPTH 7

#include "main.h"
#include "stack.h"
#include "move.h"
#include "evaluate.h"

void minimax_driver(int depth, bool isMax);

STACK_TYPE mymax(STACK_TYPE a, STACK_TYPE b);
STACK_TYPE mymin(STACK_TYPE a, STACK_TYPE b);
STACK_TYPE minimax(int depth, bool isMax, bool isFinal);

#endif