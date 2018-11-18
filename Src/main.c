#include "../Inc/main.h"
#include "../Inc/stack.h"
#include "../Inc/move.h"
#include "../Inc/evaluate.h"
#include "../Inc/ai.h"

void initMap(void);
void printMap(void);
void initTimer(void);
void test(void);
VOID CALLBACK clockTimer(PVOID, BOOLEAN);

int main(void)
{
    printf("Starting the GAME!\n\n");

    ballX = row / 2;
    ballY = col / 2;
    upSide = true;

    initMap();
    currentStack = sInit(1000 * row * col);
    dfsStack = sInit(1000);
    moveStack = sInit(1000);
    moveMax = sInit(1000);
    initTimer();

    test();
    // return 0;

    int loop = 99;
    while (loop--)
    {
        // printf("ballX is %d ballY is %d\n", ballX, ballY);
        minimax_driver(0, true);
        printf("out %d\n", sSize(moveMax));
        for (int i = 0; i < sSize(moveMax); i++)
        {
            printf("move is: 0x%02X\n", sGet(moveMax, i).move);
            applyMove(sGet(moveMax, i));
            printMap();
        }
        sClear(moveMax);

        int oppMove = 'a';
        STACK_TYPE oppTmp;
        scanf("%d", &oppMove);
        oppTmp.move = oppMove;
        printf("oppMove is: 0x%02X\n", oppMove);
        applyMove(oppTmp);
        printMap();
    }
    return 0;
}

void initMap(void)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            map[i][j] = 0x00;

    for (int j = 0; j < col; j++)
    {
        map[0][j] = 0xFF;
        map[row - 1][j] = 0xFF;
    }

    for (int i = 1; i < row - 1; i++)
    {
        map[i][0] = 0xF1;
        map[i][col - 1] = 0x1F;
    }

    for (int j = 0; j < col; j++)
    {
        map[1][j] = 0xC7;
        map[row - 2][j] = 0x7C;
    }

    for (int j = 0; j < col; j++)
        map[row / 2][j] = 0x44;

    map[row / 2][0] = 0xF5;
    map[row / 2][col - 1] = 0x5F;

    map[1][0] = 0xF7;
    map[1][col - 1] = 0xDF;
    map[row - 2][0] = 0xFD;
    map[row - 2][col - 1] = 0x7F;

    map[0][(col / 2) - 1] = 0xF7;
    map[0][(col / 2)] = 0xC7;
    map[0][(col / 2) + 1] = 0xDF;

    map[1][(col / 2) - 1] = 0xC1;
    map[1][(col / 2)] = 0x00;
    map[1][(col / 2) + 1] = 0x07;

    map[row - 1][(col / 2) - 1] = 0xFD;
    map[row - 1][(col / 2)] = 0x7C;
    map[row - 1][(col / 2) + 1] = 0x7F;

    map[row - 2][(col / 2) - 1] = 0x70;
    map[row - 2][(col / 2)] = 0x00;
    map[row - 2][(col / 2) + 1] = 0x1C;
}

void printMap(void)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            if (ballX == i && ballY == j)
                printf("0Z%02X  ", map[i][j]);
            else
                printf("0x%02X  ", map[i][j]);

            if (j == col - 1)
                printf("\n");
        }
    printf("\n\n");
}

void initTimer(void)
{
    HANDLE hTimer = NULL;
    HANDLE hTimerQueue = NULL;
    int arg = 123;

    // Use an event object to track the TimerRoutine execution
    gDoneEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (NULL == gDoneEvent)
    {
        printf("CreateEvent failed (%d)\n", GetLastError());
        return;
    }

    // Create the timer queue.
    hTimerQueue = CreateTimerQueue();
    if (NULL == hTimerQueue)
    {
        printf("CreateTimerQueue failed (%d)\n", GetLastError());
        return;
    }

    // Set a timer to call the timer routine in 10 seconds.
    if (!CreateTimerQueueTimer(&hTimer, hTimerQueue,
                               (WAITORTIMERCALLBACK)clockTimer, &arg, clockPeriod, 1, 0))
    {
        printf("CreateTimerQueueTimer failed (%d)\n", GetLastError());
        return;
    }
}

VOID CALLBACK clockTimer(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
    if (lpParam != NULL && TimerOrWaitFired)
    {
        clock++;
    }

    SetEvent(gDoneEvent);
}

void test()
{
    /* For testing applyMove */
    // printMap();

    // STACK_TYPE temp;
    // temp.move = 0x01;
    // applyMove(temp);

    printMap();

    // reverseMove(temp);

    // printMap();

    /* For testing checkGoal */
    // upSide = true;
    // ballX = 0;
    // ballY = col / 2 + 1;
    // printf("check goal: %d \n", checkGoal());

    /* To test evaluate() */
    // upSide = true;
    // ballX = row / 2 ;
    // ballY = col / 2 + 4;
    // printf("evaluate: %d", evaluateState());
}
