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

    int children = findMove();
    STACK_TYPE max, tmp;
    max.value = -(1 << 30);

    for (int i = 0; i < children; i++)
    {
        STACK_TYPE child = sPop(currentStack);
        // printf("child number %d is: 0x%02X\n", i, child.move);
        applyMove(child);
        tmp = minimax(depth + 1, false);
        if (tmp.value > max.value)
        {
            max.move = child.move;
            max.value = tmp.value;
            // printf("better move is: 0x%02X \n", max.move);
        }
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
        tmp.move = sPeek(doneStack).move;
        // printf("debug move 0x%02X", tmp.move);
        return tmp;
    }
    int children = findMove();
    if (isMax)
    {
        STACK_TYPE max;
        max.value = -(1 << 30);
        for (int i = 0; i < children; i++)
        {
            STACK_TYPE child = sPop(currentStack);
            applyMove(child);
            // sPush(child, doneStack);
            max = mymax(max, minimax(depth + 1, false));
            // STACK_TYPE lastMove = sPop(doneStack);
            reverseMove(child);
        }
        return max;
    }
    else
    {
        STACK_TYPE min;
        min.value = 1<<30;
        for (int i = 0; i < children; i++)
        {
            STACK_TYPE child = sPop(currentStack);
            applyMove(child);
            // sPush(child, doneStack);
            min = mymin(min, minimax(depth + 1, true));
            // STACK_TYPE lastMove = sPop(doneStack);
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