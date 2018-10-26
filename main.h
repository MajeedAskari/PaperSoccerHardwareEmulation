#define row 13
#define col 9

enum States {start, oppTurn, ourTurn, findingMove, moveTransfer};

enum States currentState, nextState;
unsigned char map[row][col];
int currentStack, doneStack;
