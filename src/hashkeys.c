#include <stdlib.h>

#include "hashkeys.h"
#include "globals.h"
#include "board.h"
#include "enums.h"

U64 hashPiece (U64 key, int piece, int sq) {
    return key ^= pieceKeys[piece][sq];
}

U64 hashCastle (BOARD *pos) {
    return pos->posKey ^= castleKeys[pos->castlePermission];
}

U64 hashSide (BOARD *pos) {
    return pos->posKey ^= sideKey;
}

U64 hashEnPassant (BOARD *pos) {
    return pos->posKey ^= pieceKeys[EMPTY][pos->enPassant];
}

/**
 * @brief generate a random unsigned 64-bit integer.
 *
 * @return a random 64-bit integer.
 */
U64 generateRandomU64 () {
    return ((U64)random() << 32) | random();
}

/**
 * @brief generate a hash key for a given position.
 *
 * @param pos (*BOARD) the given position.
 *
 * TODO: describe how it works
 *
 * @return (U64) the hash key of the position.
 */
U64 generatePositionKey (const BOARD *pos) {
    U64 finalKey = 0;
    int piece;

    for (int i = 0; i < BOARD_SQUARES; ++i) {
        piece = pos->pieces[i];
        if (piece != EMPTY && piece != OFF_BOARD && piece != SQ_NONE) {
            ASSERT(piece >= P && piece <= k);
            finalKey ^= pieceKeys[piece][i];
        }
    }

    if (pos->sideToMove == WHITE)
        finalKey ^= sideKey;

    if (pos->enPassant != SQ_NONE) {
        ASSERT(pos->enPassant >= 0 && pos->enPassant < BOARD_SQUARES);
        finalKey ^= pieceKeys[EMPTY][pos->enPassant];
    }

    ASSERT(pos->castlePermission >= 0 && pos->castlePermission <= 15);

    finalKey ^= castleKeys[pos->castlePermission];

    return finalKey;
}