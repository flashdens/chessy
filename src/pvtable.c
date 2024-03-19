#include <stdlib.h>
#include <string.h>

#include "milochess.h"

PVTABLE* pvtNew () {
    const int pvSize = 0x100000 * 2;
    PVTABLE *table = malloc(pvSize);
    table->itemsNum = (pvSize / sizeof (S_PVENTRY)) - 2;
    table->items = calloc((size_t)table->itemsNum, sizeof(S_PVENTRY));
    printf("table initialized with %d entries\n", table->itemsNum);
    return table;
}

static void pvtDelEntry (S_PVENTRY *e) {
    free(e);
}

void pvtClear (struct BOARD *pos) {
    free(pos->pvTable);
    pos->pvTable = pvtNew();
}

void pvtInsert (struct BOARD *pos, int move) {
    int i = pos->posKey % pos->pvTable->itemsNum;

    ASSERT(i >= 0 && i <= pos->pvTable->itemsNum - 1);

    pos->pvTable->items[i].move = move;
    pos->pvTable->items[i].posKey = pos->posKey;
}

int pvtProbe (struct BOARD *pos) {
    int index = pos->posKey % pos->pvTable->itemsNum;

    ASSERT(index >= 0 && index <= pos->pvTable->itemsNum - 1);

    if (pos->pvTable->items[index].posKey == pos->posKey)
        return pos->pvTable->items[index].move;
    else
        return NOMOVE;
}

int getPVLine(const int depth, struct BOARD *pos) {
    ASSERT(depth < MAX_DEPTH)

    int move = pvtProbe(pos);
    int moveCount = 0;

    while (moveCount < depth && move != NOMOVE) {
        ASSERT(moveCount < MAX_DEPTH);

        if (moveExists(pos, move)) {
            makeMove(pos, move);
            pos->pvArray[moveCount] = move;
            moveCount++;
        }
        else {
            break;
        }

        move = pvtProbe(pos);
    }

    while (pos->ply > 0) {
        takeBackMove(pos);
    }

    return moveCount;
}