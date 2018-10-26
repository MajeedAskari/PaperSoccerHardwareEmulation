#include <stdlib.h>

#define STACK_TYPE int
#define NUMBER_OF_STACKS 10

int sInit(int stackSize);
void sDeInit(void);
void sPush(STACK_TYPE data, int stackID);
STACK_TYPE sPop(int stackID);
