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
    doneStack = sInit(1000 * row * col);
    initTimer();

    // test();
    // return 0;
    
    int loop = 99;
    while (loop--)
    {
        // printf("ballX is %d ballY is %d\n", ballX, ballY);
        STACK_TYPE ans = minimax_driver(0, true);
        printf("move is: 0x%02X\n", ans.move);
        applyMove(ans);
        printMap();

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
        map[i][0] = 0x0E;       // 0000 1110
        map[i][col - 1] = 0xE0; // 1110 0000
    }

    for (int j = 0; j < col; j++)
    {
        map[1][j] = 0x38;       // 0011 1000
        map[row - 2][j] = 0x83; // 1000 0011
    }

    for (int j = 0; j < col; j++)
        map[row / 2][j] = 0x44; // 0100 0100

    map[row / 2][0] = 0x0A;
    map[row / 2][col - 1] = 0xA0;

    map[1][0] = 0x08;             // 0000 1000
    map[1][col - 1] = 0x20;       // 0010 0000
    map[row - 2][0] = 0x02;       // 0000 0010
    map[row - 2][col - 1] = 0x80; // 1000 0000

    map[0][(col / 2) - 1] = 0x08; // 0000 1000
    map[0][(col / 2)] = 0x38;     // 0011 1000
    map[0][(col / 2) + 1] = 0x20; // 0010 0000

    map[1][(col / 2) - 1] = 0x3E; // 0011 1110
    map[1][(col / 2)] = 0x00;     // 0000 0000
    map[1][(col / 2) + 1] = 0xF8; // 1111 1000

    map[row - 1][(col / 2) - 1] = 0x02; // 0000 0010
    map[row - 1][(col / 2)] = 0x83;     // 1000 0011
    map[row - 1][(col / 2) + 1] = 0x80; // 1000 0000

    map[row - 2][(col / 2) - 1] = 0x8F; // 1000 1111
    map[row - 2][(col / 2)] = 0x00;     // 0000 0000
    map[row - 2][(col / 2) + 1] = 0xE3; // 1110 0011
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

    // printMap();

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
