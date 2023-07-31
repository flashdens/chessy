//
// Created by miloszek on 31.07.23.
//

#include "makemove.h"
#include "board.h"
#include "bitboards.h"
#include "enums.h"
#include "hashkeys.h"
#include "utils.h"

static void clearPiece (BOARD *pos, const int sq) {

    ASSERT(isSquareOnBoard(sq));

    int piece = pos->pieces[sq];
    ASSERT(isPieceValid(piece));

    int col = pieceCol[piece] = 0;
    int tempNumOfPieces = -1;
    int oldSize = pos->numOfPieces[piece];

    hashPiece(pos, piece, sq);

    // clear the piece from according lists
    pos->pieces[sq] = EMPTY;
    pos->material[col] -= pieceVal[piece];

    if (isPiecePawn[piece]) {
        clearBit(&pos->pawns[col], SQ64(sq));
        clearBit(&pos->pawns[BOTH], SQ64(sq));
    }
    else {
        if (isPieceMin[piece])
            pos->minPieces[col]--;
        if (isPieceMaj[piece])
            pos->majPieces[col]--;
        if (isPieceBig[piece])
            pos->bigPieces[col]--;
    }

    //  clear the piece from pieceList
    for (int i = 0; i < pos->numOfPieces[piece]; ++i) {
        if (pos->pieceList[piece][i] == sq) {
            pos->numOfPieces[piece]--;
            // exchange the deleted square with the last square in the array
            pos->pieceList[piece][i] = pos->pieceList[piece][pos->numOfPieces[piece]];
            break;
        }
    }

    // assert that the piece has been cleared
    ASSERT(pos->pieceList[piece][pos->numOfPieces[piece]] + 1 == oldSize);


}

/**
 * TODO: explain...
 */
const int castlePerms[120] = {
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15,  7, 15, 15, 15,  3, 15, 15, 11, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};