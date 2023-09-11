#include <stdlib.h>

#include "pvtable.h"
#include "utils.h"
#include "board.h"


PVTABLE* pvtNew () {
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

void pvtInsert (PVTABLE *t, BOARD *pos, int move) {
    int index = pos->posKey % t->itemsNum;

    ASSERT(index >= 0 && index <= t->itemsNum - 1);

    PVENTRY *e = malloc(sizeof(PVENTRY));

    t->items[index].move = move;
    t->items[index].posKey = pos->posKey;
}

int pvtProbe (PVTABLE *t, BOARD *pos) {
    int index = pos->posKey % t->itemsNum;

    ASSERT(index >= 0 && index <= t->itemsNum - 1);

    if (t->items[index].posKey == pos->posKey)
        return t->items[index].move;

    return NOMOVE;
}

//int pvtRetrieve () {
//
//
//}