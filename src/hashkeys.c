#include "hashkeys.h"
#include "globals.h"
#include "board.h"
#include "enums.h"

/**
 * @brief generate a hash key for a given position.
 *
 * @param pos [*BOARD] a pointer to the given board state.
 *
 * @return [U64] the hash key of the position.
 */
U64 generatePositionKey (const BOARD *pos) {
    U64 finalKey = 0;
    int piece;

    for (int i = 0; i < BOARD_SQUARES; ++i) {
        piece = pos->pieces[i];
        if (piece != SQ_NONE && piece != EMPTY) {
            ASSERT(piece >= wP && piece <= bK);
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