#include <stdlib.h>
#include <string.h>

#include "pvtable.h"
#include "utils.h"
#include "move.h"
#include "makemove.h"
#include "board.h"

PVTABLE* pvtNew () {
    const int pvSize = 0x100000 * 2;
    PVTABLE *table = malloc(pvSize);
    table->itemsNum = (pvSize / sizeof (PVENTRY)) - 2;
    free(table->items);
    table->items = calloc((size_t)table->itemsNum, sizeof(PVENTRY));
    printf("table initialized with %d entries\n", table->itemsNum);
    return table;
}

static void pvtDel (PVENTRY *e) {
    free(e);
}

void pvtClear (struct BOARD *pos) {
    memset(pos->pvTable, 0, sizeof(PVTABLE));
    free(pos->pvTable);
    pos->pvTable = NULL;
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

    while (moveCount < depth && moveExists(pos, move)) {
        ASSERT(moveCount < MAX_DEPTH);

        makeMove(pos, move);
        pos->pvArray[moveCount++] = move;

        move = pvtProbe(pos);
        if (move == NOMOVE)
            break;
    }

    while (pos->ply > 0) {
        takeBackMove(pos);
    }

    return moveCount;
}