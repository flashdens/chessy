#ifndef MILOCHESS_PVTABLE_H
#define MILOCHESS_PVTABLE_H

#include "utils.h"

typedef struct {
    U64 posKey;
    int move;
} PVENTRY;

typedef struct {
    PVENTRY *items;
    int itemsNum;
    int size;
} PVTABLE;

PVTABLE* newPVTable ();

#endif //MILOCHESS_PVTABLE_H
