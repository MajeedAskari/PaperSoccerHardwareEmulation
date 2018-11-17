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
STACK_TYPE minimax_driver(int depth, bool isMax)
{

    int children = findMove(currentStack);
    STACK_TYPE max, tmp, curChild, curMove;
    max.value = -(1 << 30);
    int dfsStack = sInit(1000);
    int moveStack = sInit(1000);
    int moveMax = sInit(1000);

    for (int i = 0; i < children; i++)
    {
        // TODO: check if currentStack is the same before and after minimax
        STACK_TYPE child = sPop(currentStack);
        applyMove(child);
        sPush(child, dfsStack);

        do
        {
            while (curChild.finalMove != true && sSize(dfsStack) != 0)
            {
                STACK_TYPE curMove = sPop(dfsStack);
                sPush(curMove, moveStack);
                applyMove(curMove);
                findMove(dfsStack);
            }
            if (sSize(dfsStack) == 0)
                continue;

            tmp = minimax(depth + 1, false);
            if (tmp.value > max.value)
            {
                max.value = tmp.value;
                sCopyStack(moveStack, moveMax);
            }
            reverseMove(curMove);
            sPop(moveStack);
        } while (sSize(dfsStack) != 0);


        reverseMove(child);
    }
    return max;
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
            sPush(child, doneStack);
            max = mymax(max, minimax(depth + 1, !child.finalMove));
            STACK_TYPE lastMove = sPop(doneStack);
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
            sPush(child, doneStack);
            min = mymin(min, minimax(depth + 1, child.finalMove));
            STACK_TYPE lastMove = sPop(doneStack);
            reverseMove(child);
        }
        return min;
    }
}

// int main()
// {

//     int res = minimax(0, true);
//     printf("The optimal value is : %d \n", res);
//     return 0;
// }