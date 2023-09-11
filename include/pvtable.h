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

void pvtInsert (PVTABLE *t, BOARD *pos, int move);

static void pvtDel (PVENTRY *e);

void pvtClear (PVTABLE *t);

int pvtProbe (PVTABLE *t, BOARD *pos);

#endif //MILOCHESS_PVTABLE_H
