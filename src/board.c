#include "board.h"
#include "enums.h"
#include "globals.h"

void resetBoard (BOARD *pos) {
    for (int i = 0; i < BOARD_SQUARES; ++i) {
        pos->pieces[i] = OFF_BOARD;
    }

    for (int i = 0; i < 64; ++i) {
        pos->pieces[SQ120(i)] = EMPTY;
    }

    for (int i = 0; i < 3; ++i) {
        pos->bigPieces[i] = 0;
        pos->majorPieces[i] = 0;
        pos->minorPieces[i] = 0;
        pos->pawns[i] = 0LL;
    }

    for (int i = 0; i < 13; ++i) {
        pos->pieceNumber[i] = 0;
    }

    pos->kingSquare[WHITE] = pos->kingSquare[BLACK] = SQ_NONE;

    pos->sideToMove = BOTH;
    pos->enPassant = SQ_NONE;
    pos->fiftyMove = 0;

    pos->ply = 0;
    pos->hisPly = 0;

    pos->castlePermission = 0;

    pos->posKey = 0ULL;

    //TODO: piece list
}