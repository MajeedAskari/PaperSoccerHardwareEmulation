#include "main.h"
#include "stack.h"

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
