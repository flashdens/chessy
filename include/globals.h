#ifndef MILOCHESS_GLOBALS_H
#define MILOCHESS_GLOBALS_H

#include <stdbool.h>

#include "utils.h"

#define BOARD_SQUARES 120
#define MAX_MOVES 2048

extern int Sq120ToSq64[BOARD_SQUARES];
extern int Sq64ToSq120[64];

extern U64 setMask[64];
extern U64 clearMask[64];

extern U64 pieceKeys[13][120];
extern U64 sideKey;
extern U64 castleKeys[16];

extern char pieceChar[];
extern char sideChar[];
extern char rankChar[];
extern char fileChar[];

extern bool isPieceMin[13];
extern bool isPieceBig[13];
extern bool isPieceMaj[13];
extern int pieceVal[13];
extern int pieceCol[13];

extern int boardFiles[BOARD_SQUARES];
extern int boardRanks[BOARD_SQUARES];

extern const int knightDir[8];
extern const int rookDir[4];
extern const int bishopDir[4];
extern const int kingDir[8];

extern bool isPieceKnight[13];
extern bool isPieceKing[13];
extern bool isPieceBishopOrQueen[13];
extern bool isPieceRookOrQueen[13];

/**
 * @brief print the coordinates of a square.
 *
 * @param sq the square
 *
 * @return (*char) printSq
 */
char* printSquare (int sq);

extern char* printMove (int move);


#endif
