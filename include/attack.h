/**
 * @file attack.h
 * @brief Function declarations for attack.c - check a square for attacks coming from other pieces.
 */


#ifndef MILOCHESS_ATTACK_H
#define MILOCHESS_ATTACK_H

#include <stdbool.h>
#include "board.h"


/**
 * @brief check the square for pawn attacks.
 *
 * @param square (const int) the analyzed square
 * @param side (const int) the side whose turn it is
 * @param pos (const *BOARD) the current position
 *
 * @return true if the square is attacked
 * @return false otherwise
 */
bool attackedByPawn(int square, int side, const BOARD *pos);

/**
 * @brief check the square for knight attacks.
 *
 * @param square (const int) the analyzed square
 * @param side (const int) the side whose turn it is
 * @param pos (const *BOARD) the current position
 *
 * @return true if the square is attacked
 * @return false otherwise
 */
bool attackedByKnight(int square, int side, const BOARD *pos);

/**
 * @brief check the square for rook and straight queen attacks.
 *
 * the function checks if there's a piece of the opposing color standing in a straight line from a square.
 * if a piece is found such way, and it's a rook/queen, the square is considered attacked.
 *
 * @param square (const int) the analyzed square
 * @param side (const int) the side whose turn it is
 * @param pos (const *BOARD) the current position
 *
 * @return true if the square is attacked
 * @return false otherwise
 */
bool attackedByRookOrQueen(int square, int side, const BOARD *pos);

/**
 * @brief check the square for bishop and diagonal queen attacks.
 *
 * the function checks if there's a piece of the opposing color standing in a diagonal line from a square.
 * if a piece is found such way, and it's a bishop/queen, the square is considered attacked.
 *
 * @param square (const int) the analyzed square
 * @param side (const int) the side whose turn it is
 * @param pos (const *BOARD) the current position
 *
 * @return true if the square is attacked
 * @return false otherwise
 */
bool attackedByBishopOrQueen(int square, int side, const BOARD *pos);

/**
 * @brief check the square for king attacks.
 *
 * @param square (const int) the analyzed square
 * @param side (const int) the side whose turn it is
 * @param pos (const *BOARD) the current position
 *
 * @return true if the square is attacked
 * @return false otherwise
 */
bool attackedByKing(int square, int side, const BOARD *pos);

/**S
 * @brief check the square for attacks coming from the opposing pieces.
 *
 * this is the driver function for attack.c to rule them all.
 *
 * @param square (const int) the analyzed square
 * @param side (const int) the side whose turn it is
 * @param pos (const *BOARD) the current position
 *
 * @return true if the square is attacked
 * @return false otherwise
 */
bool isSquareAttacked(int square, int side, const BOARD *pos);

#endif // MILOCHESS_ATTACK_H
