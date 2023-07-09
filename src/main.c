#include <stdio.h>
#include "init.h"
#include "enums.h"
#include "board.h"

int main() {
    initAll();
    int hehe = 2;
    int xd = 4;
    ASSERT(hehe == xd)
    printf("it works!");
    return 0;
}
