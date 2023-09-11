#ifndef MILOCHESS_PVTABLE_H
#define MILOCHESS_PVTABLE_H

#include "utils.h"

typedef struct BOARD;

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

void pvtInsert (PVTABLE *t, struct BOARD *pos, int move);

static void pvtDel (PVENTRY *e);

void pvtClear (PVTABLE *t);

int pvtProbe (struct BOARD *pos);

#endif //MILOCHESS_PVTABLE_H
