#include "../Inc/main.h"
#include "../Inc/evaluate.h"

int evaluateState()
{
    int ballX2 = ballX;
    int g = checkGoal();
    if (g == GOAL_VALUE || g == -GOAL_VALUE)
        return g;

    if (!upSide)
    {
        ballX2 = row - ballX2 - 1;
    }

    int eval = 0;
    if (ballX2 == row - 2)
    {
        if (ballY == col / 2 || ballY == col / 2 - 1 || ballY == col / 2 + 1)
            eval += 99999;
    }
    eval += (ballX2 - (row / 2)) * 5;
    // if (ballY <= col / 2)
    //     eval += ballY * 5;
    // else
    //     eval += (col - ballY) * 5;

    return eval;
}

int checkGoal()
{
    if (ballY == col / 2 || ballY == col / 2 + 1 || ballY == col / 2 - 1)
    {
        if ((ballX == 0 && !upSide) || (ballX == row - 1 && upSide))
            return GOAL_VALUE;
        if ((ballX == 0 && upSide) || (ballX == row - 1 && !upSide))
            return -GOAL_VALUE;
    }
    
    return 0;
}
