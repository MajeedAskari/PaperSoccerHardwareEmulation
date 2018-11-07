#include "../Inc/ai.h"

// Returns the optimal value a maximizer can obtain.
// depth is current depth in game tree.
// nodeIndex is index of current node in scores[].
// isMax is true if current move is
// of maximizer, else false
// scores[] stores leaves of Game tree.
// h is maximum height of Game tree

int minimax(int depth, bool isMax)
{

    if (depth == MAX_DEPTH)
        return evaluateState();

    STACK_TYPE par = sPop(currentStack);
    applyMove(par);
    int children = findMove();
    par.children = children;

    if (isMax)
    {
        int max = -INFINITE;
        for (int i = 0; i < children; i++)
        {
            max = max(max, minimax(depth + 1, false));
        }
        return max;
    }
    else
    {
        int min = INFINITE;
        for (int i = 0; i < children; i++)
        {
            min = min(min, minimax(depth + 1, true));
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