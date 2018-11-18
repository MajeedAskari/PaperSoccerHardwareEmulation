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
    int d = 0;
    for (int i = 0; i < children; i++)
    {
        // TODO: check if currentStack is the same before and after minimax
        STACK_TYPE child = sPop(currentStack);

        if (child.finalMove != true)
        {
            sPush(child, dfsStack);
            curMove = child;
            d = 0;
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
                    break;
                }
                tmp = minimax(depth + 1, false, true);
                if (tmp.value > max.value)
                {
                    max.value = tmp.value;
                    sCopyStack(moveStack, moveMax);
                    printf("line 59 %d    %d\n", sSize(moveStack), sSize(moveMax));
                }
                d++;
                reverseMove(curMove);
                sPop(moveStack);
                printf("line 64\n");
            } while (sSize(dfsStack) != 0 && d < MAX_DEPTH);
        }
        else
        {

            applyMove(child);
            sPush(child, moveStack);
            tmp = minimax(depth + 1, false, true);
            if (tmp.value > max.value)
            {
                max.value = tmp.value;
                sCopyStack(moveStack, moveMax);
                printf("line 75 %d    %d\n", sSize(moveStack), sSize(moveMax));
            }
            // reverseMove(child);
            // sPop(moveStack);
        }

        sPop(moveStack);
        // TODO: ensure that moveStack is empty here
        reverseMove(child);
    }
}

// isMax is true if current move is
// of maximizer, else false
STACK_TYPE minimax(int depth, bool isMax, bool isFinal)
{

    if (depth >= MAX_DEPTH)
    {
        STACK_TYPE tmp;
        tmp.value = evaluateState();
        // printf("line 95 %d %d\n", depth, isFinal);
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
            max = mymax(max, minimax(depth + 1, !child.finalMove, child.finalMove));
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
            min = mymin(min, minimax(depth + 1, child.finalMove, child.finalMove));
            reverseMove(child);
        }
        return min;
    }
}
