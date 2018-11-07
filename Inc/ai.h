#ifndef AI_H_
#define AI_H_

#define MAX_DEPTH 5

#include "main.h"
#include "stack.h"
#include "move.h"
#include "evaluate.h"

int minimax(int depth, bool isMax);

#endif