#include <stdio.h>
#include "stack.h"
#include "main.h"

char *findMove()
{

    if (map[x][y - 1] != NULL && (map[x][y - 1] & 1 == 0))
    {
        sPush(1, current);
    }
    if (map[x + 1][y - 1] != NULL && (map[x + 1][y - 1] & 2 == 0))
    {
        sPush(2, current);
    }
    if (map[x + 1][y] != NULL && (map[x + 1][y] & 4 == 0))
    {
        sPush(4, current);
    }
    if (map[x + 1][y + 1] != NULL && (map[x + 1][y + 1] & 8 == 0))
    {
        sPush(8, current);
    }
    if (map[x][y + 1] != NULL && (map[x][y + 1] & 16 == 0))
    {
        sPush(16, current);
    }
    if (map[x - 1][y + 1] != NULL && (map[x - 1][y + 1] & 32 == 0))
    {
        sPush(32, current);
    }
    if (map[x - 1][y] != NULL && (map[x - 1][y] & 64 == 0))
    {
        sPush(64, current);
    }
    if (map[x - 1][y - 1] != NULL && (map[x - 1][y - 1] & 128 == 0))
    {
        sPush(128, current);
    }
}

int main()
{
    printf("%d", 65 & 61);

    return 0;
}


