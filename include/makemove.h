/**
 * @file makemove.h
 *
 * @brief contains functions needed for the engine to make actual moves.
 */

#ifndef MILOCHESS_MAKEMOVE_H
#define MILOCHESS_MAKEMOVE_H

#include "board.h"

/**
 * @brief clear a piece from the board.
 *
 * @param pos (*BOARD) the board to remove the piece from
 * @param sq the square the piece is on
 *
 * @return static void
 */
static void clearPiece (BOARD *pos, int sq);

/**
 * @brief add a piece to the board.
 *
 * @param pos (*BOARD) the board to add the piece to
 * @param sq the square to add the piece to
 *
 * @return static void
 */
static void addPiece (BOARD *pos, int sq, int piece);

/**
* @brief move a piece on the board from one square to another.
*
* @param pos (*BOARD) the board to be processed
* @param fromSq the square the piece is standing on
* @param toSq the square to move the piece to
*
* @return static void
*/
static void movePiece (BOARD *pos, int fromSq, int toSq);

/**
* @brief make a move from one square to another.
*
* @param pos (*BOARD) the board to be processed
* @param move the move to be processed @see move.h MOVE->info
*
* @return true if the move is valid
* @return false if the move is invalid (it doesn't prevent an enemy check or caused it)
 */
bool makeMove (BOARD *pos, int move);

/**
 * @brief take back a move (load the previous one from the HISTORY).
 *
 * @param pos (*BOARD) the board to be processed
 *
 * @return (bool) true on success
 * @return (program exit with code) 1 on assertion fault, alongside with according information.
 */
bool takeBackMove (BOARD *pos);

#endif //MILOCHESS_MAKEMOVE_H
