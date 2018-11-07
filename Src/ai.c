#include "../Inc/ai.h"

// isMax is true if current move is
// of maximizer, else false
int minimax(int depth, bool isMax)
{

    if (depth == MAX_DEPTH)
        return evaluateState();

    int children = findMove();



    if (isMax)
    {
        int max = -INFINITE;
        for (int i = 0; i < children; i++)
        {
            STACK_TYPE par = sPop(currentStack);
            applyMove(par);
            sPush(par, doneStack);
            max = max(max, minimax(depth + 1, false));
            STACK_TYPE lastMove = sPop(doneStack);
            reverseMove(lastMove);
        }
        return max;
    }
    else
    {
        int min = INFINITE;
        for (int i = 0; i < children; i++)
        {
            STACK_TYPE par = sPop(currentStack);
            applyMove(par);
            sPush(par, doneStack);
            min = min(min, minimax(depth + 1, true));
            STACK_TYPE lastMove = sPop(doneStack);
            reverseMove(lastMove);
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