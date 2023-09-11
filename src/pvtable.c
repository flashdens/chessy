#include <stdlib.h>

#include "board.h"
#include "pvtable.h"
#include "utils.h"


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

void pvtInsert (PVTABLE *t, struct BOARD *pos, int move) {
//    int index = pos->posKey % t->itemsNum;
//
//    ASSERT(index >= 0 && index <= t->itemsNum - 1);
//
//    PVENTRY *e = malloc(sizeof(PVENTRY));
//
//    t->items[index].move = move;
//    t->items[index].posKey = pos->posKey;
}

int pvtProbe (struct BOARD *pos) {
//    int index = pos->posKey % pos->pvTable->itemsNum;
//
//    ASSERT(index >= 0 && index <= pos->pvTable->itemsNum - 1);
//
//    if (pos->pvTable->items[index].posKey == pos->posKey)
//        return pos->pvTable->items[index].move;
//
//    return NOMOVE;
}

int getPVLine (const int depth, BOARD *pos) {

    ASSERT(depth < MAX_DEPTH)

    int move = pvtProbe(pos);
}

//int pvtRetrieve () {
//
//
//}