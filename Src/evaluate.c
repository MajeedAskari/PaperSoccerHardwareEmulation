#include "../Inc/main.h"
#include "../Inc/evaluate.h"

int evaluateState()
{
    int Y = ballY;
    int ballY = Y;

    int g = checkGoal();
    if (g == GOAL_VALUE || g == -GOAL_VALUE)
        return g;

    if (!upSide)
    {
        ballY = row - ballY;
    }

    int eval = 0;
    if (ballY == row - 2)
    {
        if (ballX == col / 2 || ballY == col / 2 - 1 || ballY == col / 2 + 1)
            eval += 99999;
    }
    eval += (ballY - row / 2) * 5;
    if (ballX <= col / 2)
        eval += ballX * 5;
    else
        eval += (col - ballX) * 5;

    return eval;
}

int checkGoal()
{
    if (ballX == col / 2 || ballX == col / 2 + 1 || ballX == col / 2 - 1)
    {
        if ((ballY == 0 && !upSide) || (ballY == row - 1 && upSide))
            return GOAL_VALUE;
        if ((ballY == 0 && upSide) || (ballY == row - 1 && !upSide))
            return -GOAL_VALUE;
    }
}
