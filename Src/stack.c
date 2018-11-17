#include "../Inc/stack.h"

STACK_TYPE _stack[NUMBER_OF_STACKS][MAX_NUMBER_OF_ELEMENTS];

int _headIndex[NUMBER_OF_STACKS] = {0};
int _stackSize[NUMBER_OF_STACKS];
int _stackCounter = 0;

int sInit(int stackSize)
{
	_stackSize[_stackCounter] = stackSize;
	_stackCounter++;
	return (_stackCounter - 1);
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

STACK_TYPE sPeek(int stackID)
{
	if (_headIndex >= 0)
		return _stack[stackID][_headIndex[stackID]];
}

void sPrintStack(int stackID)
{
	for (int i = 0; i < _headIndex[stackID]; i++)
	{
		printf("0x%02X, ", _stack[stackID][i].move);
	}
}

int sSize(int stackID)
{
	return _headIndex[stackID];
}

void sCopyStack(int source, int dest)
{
	_headIndex[dest] = 0;
	for (int i = 0; i < _headIndex[source]; i++)
	{
		sPush(_stack[source][i], dest);
	}
}