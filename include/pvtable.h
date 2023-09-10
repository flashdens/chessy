#ifndef MILOCHESS_PVTABLE_H
#define MILOCHESS_PVTABLE_H

#include "utils.h"
#include "board.h"

typedef struct {
    U64 posKey;
    int move;
} PVENTRY;

typedef struct {
    PVENTRY *items;
    int itemsNum;
    int size;
} PVTABLE;

PVTABLE* pvtNew ();

static void pvtDel (PVENTRY *e);

void pvtClear (PVTABLE *t);

// todo: chain dependencies...
void pvtInsert (BOARD *pos, int move);

#endif //MILOCHESS_PVTABLE_H
