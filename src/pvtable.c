#include <stdlib.h>

#include "board.h"
#include "pvtable.h"
#include "utils.h"

PVTABLE* tNew () {
    PVTABLE *table = malloc(sizeof(PVTABLE));
    table->size = 64;
    table->itemsNum = 0;
    table->items = calloc((size_t)table->size, sizeof(PVENTRY));
    printf("table initialized at address %p", &table);
    return table;
}

static void pvtDel (PVENTRY *e) {
    free(e);
}

void pvtClear (PVTABLE *t) {
    for (int i = 0; i < t->size; ++i) {
        PVENTRY item = t->items[i];
        if (item.posKey != 0)
            pvtDel(&item);
    }

    free(t);
}

void pvtInsert (const BOARD *pos, int move) {
    int index = pos->posKey % pos->pvTable.itemsNum;

    ASSERT(index >= 0 && index <= pos->pvTable.itemsNum - 1);

//    PVENTRY *e = malloc(sizeof(PVENTRY));

    pos->pvTable.items[index].move = move;
    pos->pvTable.items[index].posKey = pos->posKey;
}

int pvtProbe (BOARD *pos) {
    int index = pos->posKey % pos->pvTable.itemsNum;

    ASSERT(index >= 0 && index <= pos->pvTable.itemsNum - 1);

    if (pos->pvTable.items[index].posKey == pos->posKey)
        return pos->pvTable.items[index].move;

    return NOMOVE;
}