#include "../Inc/ai.h"

STACK_TYPE mymax(STACK_TYPE a, STACK_TYPE b)
{
    if (a.value > b.value)
    {
        return a;
    }
    return b;
}
STACK_TYPE mymin(STACK_TYPE a, STACK_TYPE b)
{
    STACK_TYPE tmp;
    if (a.value < b.value)
    {
        return a;
    }
    return b;
}
// TODO: think about infinite numbers and goal values
void minimax_driver(int depth, bool isMax)
{

    int children = findMove(currentStack);
    STACK_TYPE max, tmp, curChild, curMove;
    max.value = -(1 << 30);

    for (int i = 0; i < children; i++)
    {
        // TODO: check if currentStack is the same before and after minimax
        STACK_TYPE child = sPop(currentStack);
        //applyMove(child);
        //  sPush(child, moveStack);
        if (child.finalMove != true)
        {
            sPush(child, dfsStack);
            curMove = child;
            do
            {
                while (sSize(dfsStack) != 0)
                {
                    curMove = sPop(dfsStack);
                    sPush(curMove, moveStack);
                    applyMove(curMove);
                    if (curMove.finalMove == true)
                        break;
                    findMove(dfsStack);
                }
                if (sSize(dfsStack) == 0)
                {
                    // TODO ?
                }
                // TODO depth + d
                tmp = minimax(depth + 1, false);
                if (tmp.value > max.value)
                {
                    max.value = tmp.value;
                    sCopyStack(moveStack, moveMax);
                }
                reverseMove(curMove);
                sPop(moveStack);
            } while (sSize(dfsStack) != 0);
        }

        sPop(moveStack);
        // TODO: ensure that moveStack is empty here
        reverseMove(child);
    }
}

// isMax is true if current move is
// of maximizer, else false
STACK_TYPE minimax(int depth, bool isMax)
{

    if (depth == MAX_DEPTH)
    {
        STACK_TYPE tmp;
        tmp.value = evaluateState();
        return tmp;
    }
    int children = findMove(currentStack);
    if (isMax)
    {
        STACK_TYPE max;
        max.value = -(1 << 30);
        for (int i = 0; i < children; i++)
        {
            STACK_TYPE child = sPop(currentStack);
            applyMove(child);
            max = mymax(max, minimax(depth + 1, !child.finalMove));
            reverseMove(child);
        }
        return max;
    }
    else
    {
        STACK_TYPE min;
        min.value = 1 << 30;
        for (int i = 0; i < children; i++)
        {
            STACK_TYPE child = sPop(currentStack);
            applyMove(child);
            min = mymin(min, minimax(depth + 1, child.finalMove));
            reverseMove(child);
        }
        return min;
    }
}
