#include <stdbool.h>

#include "makemove.h"
#include "board.h"
#include "movelist.h"
#include "bitboards.h"
#include "enums.h"
#include "hashkeys.h"
#include "utils.h"

static void clearPiece (BOARD *pos, const int sq) {

    ASSERT(isSquareOnBoard(sq));

    int piece = pos->pieces[sq];
    ASSERT(isPieceValid(piece));

    int col = pieceCol[piece] = 0;
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
            // exchange the deleted piece with the last piece in the array
            pos->pieceList[piece][i] = pos->pieceList[piece][pos->numOfPieces[piece]];
            break;
        }
    }

    // assert that the piece has been cleared
    ASSERT(pos->pieceList[piece][pos->numOfPieces[piece]] + 1 == oldSize);
}

static void addPiece (BOARD *pos, const int sq, const int piece) {

    ASSERT(isSquareOnBoard(sq));
    ASSERT(isPieceValid(piece));

    int col = pieceCol[piece];
    int tempNumOfPieces = -1;
    int oldSize = pos->numOfPieces[piece];

    hashPiece(pos, piece, sq);

    pos->pieces[sq] = piece;
    pos->material[col] += pieceVal[piece];

    if (isPiecePawn[piece]) {
        setBit(&pos->pawns[col], SQ64(sq));
        setBit(&pos->pawns[BOTH], SQ64(sq));
    }
    else {
        if (isPieceMin[piece])
            pos->minPieces[col]++;
        if (isPieceMaj[piece])
            pos->majPieces[col]++;
        if (isPieceBig[piece])
            pos->bigPieces[col]++;
    }

    pos->pieceList[piece][pos->numOfPieces[piece]] = sq;
    pos->numOfPieces[piece]++;
}

static void movePiece (BOARD *pos, const int fromSq, const int toSq) {

    ASSERT(isSquareOnBoard(fromSq));
    ASSERT(isSquareOnBoard(toSq));

    int piece = pos->pieces[fromSq];
    int col = pieceCol[piece];
    bool moved = FALSE;

    hashPiece(pos, piece, fromSq);
    pos->pieces[fromSq] = EMPTY;

    hashPiece(pos, piece, toSq);
    pos->pieces[toSq] = piece;

    if (isPiecePawn[piece]) {
        clearBit(&pos->pawns[col], SQ64(toSq));
        clearBit(&pos->pawns[BOTH], SQ64(toSq));
        setBit(&pos->pawns[col], SQ64(toSq));
        setBit(&pos->pawns[BOTH], SQ64(toSq));
    }

    for (int i = 0; i < pos->numOfPieces[piece]; ++i) {
        if (pos->pieceList[piece][i] == fromSq) {
            pos->pieceList[piece][i] = toSq;
            moved = true;
            break;
        }
    }

    ASSERT(moved);
}

int makeMove (BOARD *pos, int move) {

    ASSERT(checkBoard(pos));

    int from = FROMSQ(move);
    int to = TOSQ(move);
    int side = pos->sideToMove;

    ASSERT(isSquareOnBoard(from));
    ASSERT(isSquareOnBoard(to));
    ASSERT(isSideValid(side));
    ASSERT(isPieceValid(pos->pieces[from]));

    pos->history[pos->hisPly].posKey = pos->posKey;
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