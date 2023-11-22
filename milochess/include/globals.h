#ifndef MILOCHESS_GLOBALS_H
#define MILOCHESS_GLOBALS_H

#include <stdbool.h>

#include "utils.h"

#define BOARD_SQUARES 120
#define MAX_MOVES 2048
#define MAX_POSITION_MOVES 256
#define MAX_DEPTH 64

/**
 * no move found.
 */
#define NOMOVE 0

extern int Sq120ToSq64[BOARD_SQUARES];
extern int Sq64ToSq120[64];

extern U64 setMask[64];
extern U64 clearMask[64];

extern U64 pieceKeys[13][120];
extern U64 sideKey;
extern U64 castleKeys[16];

extern const char pieceChar[];
extern const char sideChar[];
extern const char rankChar[];
extern const char fileChar[];

extern const bool isPieceMin[13];
extern const bool isPieceBig[13];
extern const bool isPieceMaj[13];
extern const int pieceVal[13];
extern const int pieceCol[13];

extern int boardFiles[BOARD_SQUARES];
extern int boardRanks[BOARD_SQUARES];

extern const int knightDir[8];
extern const int rookDir[4];
extern const int bishopDir[4];
extern const int kingDir[8];

extern const bool isPiecePawn[13];
extern const bool isPieceKnight[13];
extern const bool isPieceKing[13];
extern const bool isPieceBishopOrQueen[13];
extern const bool isPieceRookOrQueen[13];
extern const bool doesPieceSlide[13];

/** @file makemove.c */
extern const int castlePerms[120];

// TODO do these functions belong here?

/**
 * @brief print the coordinates of a square.
 *
 * @param sq the square
 *
 * @return (*char) the square coordinates to be printed
 */
extern char* printSquare (int sq);

/**
 * @brief print information about a move.
 *
 * @param move the move to be printed @see move.h->MOVE
 *
 * @return (*char) the move string to be printed
 */
extern char* printMove (int move);


#endif
