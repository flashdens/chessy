    #ifndef MILOCHESS_PVTABLE_H
#define MILOCHESS_PVTABLE_H

#include "utils.h"
#include "board.h"

// TODO: deanonymize 

struct BOARD;

typedef struct {
    U64 posKey;
    int move;
} PVENTRY;

typedef struct PVTABLE {
    PVENTRY *items;
    int itemsNum;
} PVTABLE;

PVTABLE* pvtNew ();

void pvtInsert (struct BOARD *pos, int move);

static void pvtDel (PVENTRY *e);

void pvtClear (struct BOARD *pos);

int pvtProbe (struct BOARD *pos);

int getPVLine (int depth, struct BOARD *pos);

#endif //MILOCHESS_PVTABLE_H
