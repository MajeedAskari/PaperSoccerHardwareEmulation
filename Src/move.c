#include "../Inc/move.h"

// TODO: check borders.
// TODO: check consecutive moves
int findMove(int stackToPush)
{
    STACK_TYPE newNode;
    int children = 0;
    newNode.finalMove = true;

    if ((map[ballX][ballY] & 0x10) == 0)
    {
        newNode.move = 0x01;
        newNode.finalMove = ((map[ballX - 1][ballY] == 0x00)? true: false);
        sPush(newNode, stackToPush);
        children++;
    }
    if ((map[ballX][ballY] & 0x02) == 0)
    {
        newNode.move = 0x02;
        newNode.finalMove = ((map[ballX - 1][ballY + 1] == 0x00)? true: false);
        sPush(newNode, stackToPush);
        children++;
    }
    if ((map[ballX][ballY] & 0x04) == 0)
    {
        newNode.move = 0x04;
        newNode.finalMove = ((map[ballX][ballY + 1] == 0x00)? true: false);
        sPush(newNode, stackToPush);
        children++;
    }
    if ((map[ballX][ballY] & 0x08) == 0)
    {
        newNode.move = 0x08;
        newNode.finalMove = ((map[ballX + 1][ballY + 1] == 0x00)? true: false);
        sPush(newNode, stackToPush);
        children++;
    }
    if ((map[ballX][ballY] & 0x01) == 0)
    {
        newNode.move = 0x10;
        newNode.finalMove = ((map[ballX + 1][ballY] == 0x00)? true: false);
        sPush(newNode, stackToPush);
        children++;
    }
    if ((map[ballX][ballY] & 0x20) == 0)
    {
        newNode.move = 0x20;
        newNode.finalMove = ((map[ballX + 1][ballY - 1] == 0x00)? true: false);
        sPush(newNode, stackToPush);
        children++;
    }
    if ((map[ballX][ballY] & 0x40) == 0)
    {
        newNode.move = 0x40;
        newNode.finalMove = ((map[ballX][ballY - 1] == 0x00)? true: false);
        sPush(newNode, stackToPush);
        children++;
    }
    if ((map[ballX][ballY] & 0x80) == 0)
    {
        newNode.move = 0x80;
        newNode.finalMove = ((map[ballX - 1][ballY - 1] == 0x00)? true: false);
        sPush(newNode, stackToPush);
        children++;
    }
    return children;
}

void applyMove(STACK_TYPE moveNode)
{
    map[ballX][ballY] = map[ballX][ballY] | moveNode.move;

    if (moveNode.move & 0x01)
    {
        ballX -= 1;
        map[ballX][ballY] |= 0x10;
    }
    else if (moveNode.move & 0x02)
    {
        ballX -= 1;
        ballY += 1;
        map[ballX][ballY] |= 0x20;
    }
    else if (moveNode.move & 0x04)
    {
        ballY += 1;
        map[ballX][ballY] |= 0x40;
    }
    else if (moveNode.move & 0x08)
    {
        ballX += 1;
        ballY += 1;
        map[ballX][ballY] |= 0x80;
    }
    else if (moveNode.move & 0x10)
    {
        ballX += 1;
        map[ballX][ballY] |= 0x01;
    }
    else if (moveNode.move & 0x20)
    {
        ballX += 1;
        ballY -= 1;
        map[ballX][ballY] |= 0x02;
    }
    else if (moveNode.move & 0x40)
    {
        ballY -= 1;
        map[ballX][ballY] |= 0x04;
    }
    else if (moveNode.move & 0x80)
    {
        ballX -= 1;
        ballY -= 1;
        map[ballX][ballY] |= 0x08;
    }
}

void reverseMove(STACK_TYPE moveNode)
{
    if (moveNode.move & 0x01)
    {
        map[ballX][ballY] &= (0x10 ^ 0xFF);
        ballX += 1;
    }
    else if (moveNode.move & 0x02)
    {
        map[ballX][ballY] &= (0x20 ^ 0xFF);
        ballX += 1;
        ballY -= 1;
    }
    else if (moveNode.move & 0x04)
    {
        map[ballX][ballY] &= (0x40 ^ 0xFF);
        ballY -= 1;
    }
    else if (moveNode.move & 0x08)
    {
        map[ballX][ballY] &= (0x80 ^ 0xFF);
        ballX -= 1;
        ballY -= 1;
    }
    else if (moveNode.move & 0x10)
    {
        map[ballX][ballY] &= (0x01 ^ 0xFF);
        ballX -= 1;
    }
    else if (moveNode.move & 0x20)
    {
        map[ballX][ballY] &= (0x02 ^ 0xFF);
        ballX -= 1;
        ballY += 1;
    }
    else if (moveNode.move & 0x40)
    {
        map[ballX][ballY] &= (0x04 ^ 0xFF);
        ballY += 1;
    }
    else if (moveNode.move & 0x80)
    {
        map[ballX][ballY] &= (0x08 ^ 0xFF);
        ballX += 1;
        ballY += 1;
    }
    map[ballX][ballY] &= (moveNode.move ^ 0xFF);
}
