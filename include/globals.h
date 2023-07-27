#ifndef MILOCHESS_GLOBALS_H
#define MILOCHESS_GLOBALS_H

#include <stdbool.h>

#include "utils.h"

#define BOARD_SQUARES 120
#define MAX_MOVES 2048
#define MAX_POSITION_MOVES 256

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

// validate.c

/**
 * @brief check if a square is on the board.
 *
 * @param sq (const) the square to be checked
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
extern bool isSquareOnBoard (int sq);

/**
 * @brief check if it's either white or black to make a move.
 *
 * @param piece (const) the side to move
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
extern bool isSideValid (int side);

/**
 * @brief check if a file or rank is on the board.
 *
 * @param piece (const) the file or rank to be checked
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
extern bool isFileRankValid (int fr);

/**
 * @brief check if a piece is valid or empty.
 *
 * @param piece (const) the piece to be checked
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
extern bool isPieceValidOrEmpty (int piece);

/**
 * @brief check if a piece is valid (not empty).
 *
 * @param piece (const) the piece to be checked
 *
 * @return (bool) true if true
 * @return (bool) false otherwise
 */
extern bool isPieceValid (int piece);

#endif
