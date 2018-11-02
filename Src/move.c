#include "../Inc/main.h"
#include "../Inc/stack.h"
#include "../Inc/move.h"

void findMove()
{
    STACK_TYPE newNode;

    if(map[ballX][ballY - 1] & 0x01 == 0)
    {
        newNode.move = 0x01;
        sPush(newNode, currentStack);
    }
    if(map[ballX + 1][ballY - 1] & 0x02 == 0)
    {
        newNode.move = 0x02;
        sPush(newNode, currentStack);
    }
    if(map[ballX + 1][ballY] & 0x04 == 0)
    {
        newNode.move = 0x04;
        sPush(newNode, currentStack);
    }
    if(map[ballX + 1][ballY + 1] & 0x08 == 0)
    {
        newNode.move = 0x08;
        sPush(newNode, currentStack);
    }
    if(map[ballX][ballY + 1] & 0x10 == 0)
    {
        newNode.move = 0x10;
        sPush(newNode, currentStack);
    }
    if(map[ballX - 1][ballY + 1] & 0x20 == 0)
    {
        newNode.move = 0x20;
        sPush(newNode, currentStack);
    }
    if(map[ballX - 1][ballY] & 0x40 == 0)
    {
        newNode.move = 0x40;
        sPush(newNode, currentStack);
    }
    if(map[ballX - 1][ballY - 1] & 0x80 == 0)
    {
        newNode.move = 0x80;
        sPush(newNode, currentStack);
    }
}

void applyMove(STACK_TYPE moveNode)
{
    map[ballX][ballY] = map[ballX][ballY] | moveNode.move;
        
    if(moveNode.move & 0x01)
    {
        ballX -=1;
        map[ballX][ballY] |= 0x10;
    }
    else if(moveNode.move & 0x02)
    {
        ballX -= 1;
        ballY += 1;
        map[ballX][ballY] |= 0x20;
    }
    else if(moveNode.move & 0x04)
    {
        ballY += 1;
        map[ballX][ballY] |= 0x40;
    }
    else if(moveNode.move & 0x08)
    {
        ballX += 1;
        ballY += 1;
        map[ballX][ballY] |= 0x80;
    }
    else if(moveNode.move & 0x10)
    {
        ballX += 1;
        map[ballX][ballY] |= 0x01;
    }
    else if(moveNode.move & 0x20)
    {
        ballX += 1;
        ballY -= 1;
        map[ballX][ballY] |= 0x02;
    }
    else if(moveNode.move & 0x40)
    {
        ballY -= 1;
        map[ballX][ballY] |= 0x04;
    }
    else if(moveNode.move & 0x80)
    {
        ballX -= 1;
        ballY -= 1;
        map[ballX][ballY] |= 0x08;
    }
}
