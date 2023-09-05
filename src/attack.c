/**
 * @file attack.c
 * @brief check a square for attacks coming from other pieces. isSquareAttacked is the main function for this file.
 */
#include <stdbool.h>

#include "attack.h"
#include "board.h"
#include "enums.h"
#include "validate.h"

/**
 * @brief check the square for pawn attacks.
 *
 * @param square (const int) the analyzed square
 * @param side (const int) the attacking side
 * @param pos (const *BOARD) the current position
 *
 * @return true if the square is attacked
 * @return false otherwise
 */
bool attackedByPawn (const int square, const int side, const BOARD *pos) {
    if (side == WHITE) {
        if (pos->pieces[square - 11] == P || pos->pieces[square - 9] == P)
            return true;
    }
    else {
        if (pos->pieces[square + 11] == p || pos->pieces[square + 9] == p)
            return true;
    }

    return false;
}

/**
 * @brief check the square for knight attacks.
 *
 * @param square (const int) the analyzed square
 * @param side (const int) the attacking side
 * @param pos (const *BOARD) the current position
 *
 * @return true if the square is attacked
 * @return false otherwise
 */
bool attackedByKnight (const int square, const int side, const BOARD *pos) {

    int piece;

    for (int i = 0; i < 8; ++i) {
        piece = pos->pieces[square + knightDir[i]];
        if (piece != OFF_BOARD && isPieceKnight[piece] && pieceCol[piece] == side)
            return true;
    }

    return false;
}

/**
 * @brief check the square for rook and straight queen attacks.
 *
 * the function checks if there's a piece of the opposing color standing in a straight line from a square.
 *
 * if a piece is found such way and it's a rook/queen, the square is considered attacked.
 *
 * @param square (const int) the analyzed square
 * @param side (const int) the attacking side
 * @param pos (const *BOARD) the current position
 *
 * @return true if the square is attacked
 * @return false otherwise
 */
bool attackedByRookOrQueen (const int square, const int side, const BOARD *pos) {

    int dir;
    int tempSquare;
    int piece;

    for (int i = 0; i < 4; ++i) {
        dir = rookDir[i];
        tempSquare = square + dir;
        piece = pos->pieces[tempSquare];

        while (piece != OFF_BOARD) { // TODO: not sure if it works correctly
            if (piece != EMPTY) {
                if (isPieceRookOrQueen[piece] && pieceCol[piece] == side)
                    return true;    
                else
                    break;
            }

            tempSquare += dir;
            piece = pos->pieces[tempSquare];
        }
    }

    return false;
}

/**
 * @brief check the square for bishop and diagonal queen attacks.
 *
 * the function checks if there's a piece of the opposing color standing in a diagonal line from a square.
 *
 * if a piece is found such way and it's a bishop/queen, the square is considered attacked.
 *
 * @param square (const int) the analyzed square
 * @param side (const int) the attacking side
 * @param pos (const *BOARD) the current position
 *
 * @return true if the square is attacked
 * @return false otherwise
 */
bool attackedByBishopOrQueen (const int square, const int side, const BOARD *pos) {

    int dir;
    int tempSquare;
    int piece;

    for (int i = 0; i < 4; ++i) {
        dir = bishopDir[i];
        tempSquare = square + dir;
        piece = pos->pieces[tempSquare];

        while (piece != OFF_BOARD) {
            if (piece != EMPTY) {
                if (isPieceBishopOrQueen[piece] && pieceCol[piece] == side)
                    return true;
                else
                    break;
            }

            tempSquare += dir;
            piece = pos->pieces[tempSquare];
        }
    }

    return false;
}

/**
 * @brief check the square for king attacks.
 *
 * @param square (const int) the analyzed square
 * @param side (const int) the attacking side
 * @param pos (const *BOARD) the current position
 *
 * @return true if the square is attacked
 * @return false otherwise
 */
bool attackedByKing (const int square, const int side, const BOARD *pos) {

    int piece;

    for (int i = 0; i < 8; ++i) {
        piece = pos->pieces[square + kingDir[i]];
        if (piece != OFF_BOARD && isPieceKing[piece] && pieceCol[piece] == side)
            return true;
    }

    return false;
}

/**
 * @brief check the square for attacks coming from the opposing pieces.
 *
 * this is the driver function for attack.c to rule them all.
 *
 * @param square (const int) the analyzed square
 * @param side (const int) the attacking side
 * @param pos (const *BOARD) the current position
 *
 * @return true if the square is attacked
 * @return false otherwise
 */
extern bool isSquareAttacked (const int square, const int side, const BOARD *pos) {

    ASSERT(isSquareOnBoard(square));
    ASSERT(isSideValid(side));
    ASSERT(checkBoard(pos));

    if (attackedByPawn(square, side, pos) ||
    attackedByKnight(square, side, pos) ||
    attackedByRookOrQueen(square, side, pos) ||
    attackedByBishopOrQueen(square, side, pos) ||
    attackedByKing(square, side, pos))
        return true;
    else
        return false;
}

/**
 * (a utility debugging function) print all squares attacked by the given side.
 * 
 * @param side (const int) the attacking side
 * @param pos (const *BOARD) the position to be checked
 *
 * @return void
 */
__attribute__((unused)) void showAttacks (const int side, const BOARD *pos) {

    int square;

    for (int rank = RANK_8; rank >= RANK_1; --rank) {
        printf("%d ", rank + 1);
        for (int file = FILE_A; file <= FILE_H; ++file) {
            square = FR2SQ(file, rank);
            if (isSquareAttacked(square, side, pos))
                printf("  X");
            else
                printf("  -");
        }
        printf("\n");
    }
    printf("  ");
    for (int file = FILE_A; file <= FILE_H; ++file) {
        printf("%3c",'a' + file);
    }
        printf("\n\n");
}
