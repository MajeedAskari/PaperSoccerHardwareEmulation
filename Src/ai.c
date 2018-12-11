#include "../Inc/ai.h"
#include "../Inc/stack.h"

STACK_TYPE mymax(STACK_TYPE a, STACK_TYPE b)
{
    if (a.value >= b.value)
    {
        return a;
    }
    return b;
}
STACK_TYPE mymin(STACK_TYPE a, STACK_TYPE b)
{
    if (a.value <= b.value)
    {
        return a;
    }
    return b;
}
// TODO: think about infinite numbers and goal values
void minimax_driver(int depth, bool isMax)
{
	dontPrint = 1;
	sClear(currentStack);
	sClear(currentStack2);
	sClear(moveMax);
	sClear(dfsStack);
	sClear(moveStack);

    int children = findMove(currentStack2);
    STACK_TYPE max, tmp, curMove;
    max.value = -(1 << 30);
    int d = 0;
    for (int i = 0; i < children; i++)
    {
		sClear(currentStack);
		sClear(dfsStack);
		sClear(moveStack);
        STACK_TYPE child = sPop(currentStack2);

        if (child.finalMove != true)
        {
            sPush(child, dfsStack);
            curMove = child;
            d = 0;
			while (sSize(dfsStack) != 0)
			{
				curMove = sPop(dfsStack);
				sPush(curMove, moveStack);
				applyMove(curMove);
				//printf("line51\n");
				//printMap();
				if (curMove.finalMove == true) {
					//printf("line54\n");
					//printMap();
					tmp = minimax(depth + 1, false, true);
					//printf("line57\n");
					//printMap();
					if (tmp.value > max.value)
					{
						max.value = tmp.value;
						sCopyStack(moveStack, moveMax);
						// printf("line 59 %d    %d\n", sSize(moveStack), sSize(moveMax));
					}
					reverseMove(curMove);
					sPop(moveStack);
					//printf("line67\n");
					//printMap();
					do {
						STACK_TYPE sttemp = sPop(childCountHolder), sttemp2;

						if (sttemp.parChildcount == 1) {
							sttemp2.move = sttemp.parentMove;
							reverseMove(sttemp2);
							//printf("line73\n");
							//printMap();
						}
						else {
							sttemp.parChildcount--;
							sPush(sttemp, childCountHolder);
							break;
						}
					} while (1);

				}
				else {
					STACK_TYPE sttemp;
					sttemp.parentMove = curMove.move;
					sttemp.parChildcount = findMove(dfsStack);
					sPush(sttemp, childCountHolder);
				}
			}
			//reverseMove(child);
        }
        else
        {

            applyMove(child);
            sPush(child, moveStack);
			//printf("line95\n");
			//printMap();
            tmp = minimax(depth + 1, false, true);
			//printf("line98\n");
			//printMap();

            if (tmp.value > max.value)
            {
                max.value = tmp.value;
                sCopyStack(moveStack, moveMax);
            }
			//printf("line105\n");
			//printMap();
            reverseMove(child);
			//printf("line108\n");
			//printMap();

        }

        //sPop(moveStack);
        // TODO: ensure that moveStack is empty here
		//printMap();

    }
}

// isMax is true if current move is
// of maximizer, else false
STACK_TYPE minimax(int depth, bool isMax, bool isFinal)
{
	STACK_TYPE tmp;
	tmp.finalMove = true;
	if (ballX < 0 || ballY < 0)
		return tmp;
	//if (map[7][4] == 0x02 && depth == 1) {
	//	printf("buuuuuuuuuuug line 129\n");
	//	printMap();
	//}
    if (depth >= MAX_DEPTH && isFinal)
    {
        tmp.value = evaluateState();
        // printf("line 95 %d %d\n", depth, isFinal);
        return tmp;
    }
	//printMap();
    int children = findMove(currentStack);
	//if (sPeek(currentStack).move == 0x10 && map[7][4] == 0x03 && ballY == 4 && (ballX == 7 || ballX == 6)) {
	//	int dsjdvn = 0;
	//}
    if (isMax)
    {
		if(!dontPrint)
			printMap();

        STACK_TYPE max;
        max.value = -(1 << 30);
        for (int i = 0; i < children; i++)
        {
			if (!dontPrint)
				printMap();
            STACK_TYPE child = sPop(currentStack);
            applyMove(child);
			if (!dontPrint)
				printMap();
            max = mymax(max, minimax(depth + 1, !child.finalMove, child.finalMove));
			if (!dontPrint)
				printMap();
            reverseMove(child);
			if (!dontPrint)
				printMap();
        }
        return max;
    }
    else
    {
        STACK_TYPE min;
        min.value = 1 << 30;
        for (int i = 0; i < children; i++)
        {
			if (!dontPrint)
				printMap();
            STACK_TYPE child = sPop(currentStack);
			//printf("1 %02X ", map[7][4]);

            applyMove(child);
			if (!dontPrint)
				printMap();

            min = mymin(min, minimax(depth + 1, child.finalMove, child.finalMove));
			if (!dontPrint)
				printMap();
			//printf("3 %02X ", map[7][4]);

            reverseMove(child);
			if (!dontPrint)
				printMap();
			//printf("4 %02X ", map[7][4]);
        }
        return min;
    }
}
