#include "evaluate.h"

int evaluateState()
{
    if (checkGoal())
    {

    }
}

int checkGoal()
{
    if (ballX == col / 2 || ballX == col / 2 + 1 || ballX == col / 2 - 1)
    {
        if ((ballY == 0 && !upSide) || (ballY == row - 1 && upSide))
            return 999999;
        if ((ballY == 0 && upSide) || (ballY == row - 1 && !upSide))
            return -999999;
    }
}
