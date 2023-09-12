#include <stdlib.h>

#include "pvtable.h"
#include "utils.h"
#include "move.h"
#include "makemove.h"
#include "board.h"

PVTABLE* pvtNew () {
    const int pvSize = 0x100000 * 2;
    PVTABLE *table = malloc(sizeof(PVTABLE));
    table->itemsNum = pvSize / sizeof (PVENTRY) - 2;
    table->items = calloc((size_t)table->itemsNum, sizeof(PVENTRY));
    printf("table initialized with %d entries\n", table->itemsNum);
    return table;
}

static void pvtDel (PVENTRY *e) {
    free(e);
}

void pvtClear (struct BOARD *pos) {
    for (int i = 0; i < pos->pvTable->itemsNum; ++i) {
        PVENTRY item = pos->pvTable->items[i];
        if (item.posKey != 0)
            pvtDel(&item);
    }

    free(pos->pvTable);
}

void pvtInsert (struct BOARD *pos, int move) {
    int index = pos->posKey % pos->pvTable->itemsNum;

    ASSERT(index >= 0 && index <= pos->pvTable->itemsNum - 1);

    PVENTRY *e = malloc(sizeof(PVENTRY));

    pos->pvTable->items[index].move = move;
    pos->pvTable->items[index].posKey = pos->posKey;
}

int pvtProbe (struct BOARD *pos) {
    int index = pos->posKey % pos->pvTable->itemsNum;

    ASSERT(index >= 0 && index <= pos->pvTable->itemsNum - 1);

    if (pos->pvTable->items[index].posKey == pos->posKey)
        return pos->pvTable->items[index].move;

    return NOMOVE;
}

int getPVLine (const int depth, struct BOARD *pos) {

    ASSERT(depth < MAX_DEPTH)

    int move = pvtProbe(pos);
    int moveCount = 0;

    for (moveCount; moveCount < depth && move != NOMOVE; ++moveCount) {
        ASSERT(moveCount < MAX_DEPTH);

        if (moveExists(pos, move)) {
            makeMove(pos, move);
            moveCount++;
            pos->pvArray[moveCount] = move;
        }

        move = pvtProbe(pos);
    }

    while (pos->ply > 0) {
        takeBackMove(pos);
    }

    return moveCount;
}

//int pvtRetrieve () {
//
//
//}