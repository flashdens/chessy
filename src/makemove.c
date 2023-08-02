/**
 * @file makemove.c
 *
 * @brief contains function definitions and globals needed for the engine to make actual moves.
 */

#include <stdbool.h>

#include "makemove.h"
#include "board.h"
#include "move.h"
#include "bitboards.h"
#include "enums.h"
#include "hashkeys.h"
#include "utils.h"
#include "attack.h"

/**
 *  @var (int*) castlePerms[120]
 *
 *  @brief the list of castling permissions.
 *
 *  while there is a field for each square on the board, you should only care about those that
 *  correspond to the squares where the rooks are located - A1, H1, A8, F8.
 *  if a castle move is made to or from one of those squares, pos->castlePermission gets set to the value under this square.
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

/**
 * @brief clear a piece from the board.
 *
 * @param pos (*BOARD) the board to remove the piece from
 * @param sq the square the piece is on
 *
 * @return static void
 */
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

/**
 * @brief add a piece to the board.
 *
 * @param pos (*BOARD) the board to add the piece to
 * @param sq the square to add the piece to
 *
 * @return static void
 */
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

/**
* @brief move a piece on the board from one square to another.
*
* @param pos (*BOARD) the board to be processed
* @param fromSq the square the piece is standing on
* @param toSq the square to move the piece to
*
* @return static void
*/
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

/**
* @brief make a move from one square to another.
*
* @param pos (*BOARD) the board to be processed
* @param move the move to be processed @see move.h MOVE->info
*
* @return true if the move is valid
* @return false if the move is invalid (it doesn't prevent an enemy check or caused it)
 */
bool makeMove (BOARD *pos, int move) {

    ASSERT(checkBoard(pos));

    int side = pos->sideToMove;
    int fromSq = FROMSQ(move);
    int toSq = TOSQ(move);
    int captured = CAPTURED(move);
    int promotedTo = PROMOTED(move);

    ASSERT(isSquareOnBoard(fromSq));
    ASSERT(isSquareOnBoard(toSq));
    ASSERT(isSideValid(side));
    ASSERT(isPieceValid(pos->pieces[fromSq]));

    pos->history[pos->hisPly].posKey = pos->posKey;

    // handle en passant and castling flags
    if (move & FISENPASSANT) {
        (side == WHITE) ? clearPiece(pos, toSq - 10) : clearPiece(pos, toSq + 10);
    }
        // note that this one moves the rook
    else if (move & FISCASTLE) {
        switch (toSq) {
            case C1:
                movePiece(pos, A1, D1);
                break;
            case C8:
                movePiece(pos, A8, D8);
                break;
            case G1:
                movePiece(pos, H1, F1);
                break;
            case G8:
                movePiece(pos, H8, F8);
                break;
            default:
                // something must have gone terribly wrong...
                ASSERT(false);
        }
    }

    if (pos->enPassant != SQ_NONE)
        hashEnPassant(pos);

    // handle castle permissions
    hashCastlePerms(pos);

    pos->history[pos->hisPly].move = move;
    pos->history[pos->hisPly].fiftyMove = pos->fiftyMove;
    pos->history[pos->hisPly].enPassant = pos->enPassant;
    pos->history[pos->hisPly].castlePerm = pos->castlePerm;

    pos->castlePerm &= castlePerms[fromSq];
    pos->castlePerm &= castlePerms[toSq];

    hashCastlePerms(pos);

    pos->fiftyMove++;

    // handle capture
    if (captured != EMPTY) {
        ASSERT(isPieceValid(captured));
        clearPiece(pos, toSq);
        pos->fiftyMove = 0;
    }

    pos->hisPly++;
    pos->ply++;

    // handle en passant square after pawn start
    if (isPiecePawn[pos->pieces[fromSq]]) {
        pos->fiftyMove = 0;

        if (move & FISPAWNSTART) {
            if (side == WHITE) {
                pos->enPassant = fromSq + 10;
                ASSERT(boardRanks[pos->enPassant] == RANK_3);
            } else {
                pos->enPassant = fromSq - 10;
                ASSERT(boardRanks[pos->enPassant] == RANK_6);
            }
            hashEnPassant(pos);
        }
    }

    // after all the struggle, finally the piece is moved!
    movePiece(pos, fromSq, toSq);

    // handle promotions
    if (promotedTo != EMPTY) {
        ASSERT(isPieceValid(promotedTo) && !isPiecePawn[promotedTo]);
        clearPiece(pos, toSq);
        addPiece(pos, toSq, promotedTo);
    }

    // handle king square change
    if (isPieceKing[pos->pieces[toSq]])
        pos->kingSquare[pos->sideToMove] = toSq;

    // pretty clever isn't it?
    pos->sideToMove ^= 1;

    ASSERT(checkBoard(pos));

    // if we moved to an attacked square...
    if (isSquareAttacked(pos->kingSquare[side], pos->sideToMove, pos)) {
        takeBackMove(pos);
        return false;
    }

    return true;
}

/**
 * @brief take back a move (load the previous one from the HISTORY).
 *
 * @param pos (*BOARD) the board to be processed
 *
 * @return 0 on success
 * @return (program exit with code) 1 on assertion fault, alongside with according information.
 */
int takeBackMove (BOARD *pos) {

    ASSERT(checkBoard(pos));

    pos->hisPly--;
    pos->ply--;

    int move = pos->history[pos->hisPly].move;
    int fromSq = FROMSQ(move);
    int toSq = TOSQ(move);
    int captured = CAPTURED(move);
    int promotedTo = PROMOTED(move);

    ASSERT(isSquareOnBoard(fromSq));
    ASSERT(isSquareOnBoard(toSq));

    if (pos->enPassant != SQ_NONE)
        hashEnPassant(pos);
    hashCastlePerms(pos);

    pos->fiftyMove = pos->history[pos->hisPly].fiftyMove;
    pos->enPassant = pos->history[pos->hisPly].enPassant;
    pos->castlePerm = pos->history[pos->hisPly].castlePerm;

    if (pos->enPassant != SQ_NONE)
        hashEnPassant(pos);

    pos->sideToMove ^= 1;
    hashSide(pos);

    // handle en passant and castling flags
    if (move & FISENPASSANT) {
        (pos->sideToMove == WHITE)
        ? addPiece(pos, toSq - 10, p)
        : addPiece(pos, toSq + 10, P);
    }
    // note that this one moves the rook
    else if (move & FISCASTLE) {
        switch (toSq) {
            case C1:
                movePiece(pos, D1, A1);
                break;
            case C8:
                movePiece(pos, D8, A8);
                break;
            case G1:
                movePiece(pos, F1, H1);
                break;
            case G8:
                movePiece(pos, F8, H8);
                break;
            default:
                // something must have gone terribly wrong...
                ASSERT(false);
        }
    }
    movePiece(pos, toSq, fromSq);

    if (isPieceKing[pos->pieces[fromSq]])
        pos->kingSquare[pos->sideToMove] = fromSq;

    if (captured != EMPTY) {
        ASSERT(isPieceValid(captured));
        addPiece(pos, toSq, captured);
    }

    if (promotedTo != EMPTY) {
        ASSERT(isPieceValid(promotedTo) && !isPiecePawn[promotedTo]);
        // note that the piece has already been moved from toSq to fromSq
        clearPiece(pos, fromSq);
        addPiece(pos, fromSq, (pieceCol[promotedTo] == WHITE) ? P : p);
    }

    ASSERT(checkBoard(pos));

    return 0;
}

