#ifndef MILOCHESS_BOARD_H
#define MILOCHESS_BOARD_H

#include <stdlib.h>

#include "globals.h"
#include "utils.h"

typedef struct {
    int move;
    int castlePermission;
    int enPassant;
    int fiftyMove;
    U64 positionKey;

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

    U64 posKey;

    int pieceNumber[13];

    U64 pawns[3];
    int minorPieces[3];
    int majorPieces[3];
    int bigPieces[3];

    int castlePermission;

    int pieceList[13][10];

} BOARD;

#endif //MILOCHESS_BOARD_H
