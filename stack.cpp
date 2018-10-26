
#include "stack.h"

STACK_TYPE **_stack = (STACK_TYPE **)malloc(NUMBER_OF_STACKS * sizeof(STACK_TYPE *));
int _headIndex[NUMBER_OF_STACKS] = {0};
int _stackSize[NUMBER_OF_STACKS];
int _stackCounter = 0;

int sInit(int stackSize)
{
	_stack[_stackCounter] = (STACK_TYPE *)malloc(stackSize * sizeof(STACK_TYPE));
	_stackSize[_stackCounter] = stackSize;
	_stackCounter++;
	return (_stackCounter - 1);
}

void sDeInit()
{
	for (int i = 0; i < _stackCounter; i++)
		free(_stack[i]);
	free(_stack);
}

void sPush(STACK_TYPE data, int stackID)
{
	if (_headIndex[stackID] < _stackSize[stackID])
		_stack[stackID][_headIndex[stackID]++] = data;
}

STACK_TYPE sPop(int stackID)
{
	if (_headIndex >= 0)
		return _stack[stackID][--_headIndex[stackID]];
}
