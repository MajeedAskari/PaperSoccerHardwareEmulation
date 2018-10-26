#include <stdio.h>

char *findMove()
{

    if (map[x][y - 1] != NULL && (map[x][y - 1] & 1 == 0))
    {
        // stack.push()
    }
    if (map[x + 1][y - 1] != NULL && (map[x + 1][y - 1] & 2 == 0))
    {
        // stack.push()
    }
    if (map[x + 1][y] != NULL && (map[x + 1][y] & 4 == 0))
    {
        // stack.push()
    }
    if (map[x + 1][y + 1] != NULL && (map[x + 1][y + 1] & 8 == 0))
    {
        // stack.push()
    }
    if (map[x][y + 1] != NULL && (map[x][y + 1] & 16 == 0))
    {
        // stack.push()
    }
    if (map[x - 1][y + 1] != NULL && (map[x - 1][y + 1] & 32 == 0))
    {
        // stack.push()
    }
    if (map[x - 1][y] != NULL && (map[x - 1][y] & 64 == 0))
    {
        // stack.push()
    }
    if (map[x - 1][y - 1] != NULL && (map[x - 1][y - 1] & 128 == 0))
    {
        // stack.push()
    }
}

int main()
{
    printf("%d", 65 & 61);

    return 0;
}