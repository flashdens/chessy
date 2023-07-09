#ifndef MILOCHESS_BOARD_H
#define MILOCHESS_BOARD_H

#include <stdlib.h>

#include "globals.h"
#include "macros.h"

typedef struct {

    int move;
    int castlePermission;
    int enPassant;
    int fiftyMove;
    unsigned long long positionKey;

} HISTORY;

typedef struct {

    HISTORY history[MAX_MOVES];
    int pieces[BOARD_SQUARES];

    int kingSquare[2];

    int sideToMove;
    int enPassant;
    int fiftyMove;

    int ply;
    int hisPly;

    unsigned long long posKey;

    int pieceNumber[13];

    unsigned long long pawns[3];
    int minorPieces[3];
    int majorPieces[3];
    int bigPieces[3];

    int castlePermission;

    int pieceList[13][10];



} BOARD;

#endif //MILOCHESS_BOARD_H
