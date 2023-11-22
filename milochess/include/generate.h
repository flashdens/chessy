/**
 * @file generate.h
 * @brief includes function declarations and macros for move generation (generate.c).
 */

#include "board.h"
#include "move.h"


/** @brief generate a move integer from parameters.
 *
 * @param from from square
 * @param to to square
 * @param capture captured piece (if so)
 * @param promote promoted to piece (if so)
 * @param fl a flag to be processed (if so)
 *
 */

#ifndef MILOCHESS_GENERATE_H
#define MILOCHESS_GENERATE_H

#define MOVE(from,to,capture,promote,fl) ( (from) | ((to) << 7) | ( (capture) << 14 ) | ( (promote) << 20 ) | (fl))

/**
 * @brief add a quiet move to the move list.
 *
 * a move is considered quiet if it's not a capture, not a check or not a significant threat to the opponent.
 *
 * @param pos (const *BOARD) the position
 * @param list (*MOVELIST) the move list to append the move
 * @param move the move to be added to the move list
 *
 * @return static void
 */
static void addQuietMove (const BOARD *pos, MOVELIST *list, int move);

/**
 * @brief add a static move to the move list.
 *
 * a move is considered quiet if it's not a capture, not a check or not a significant threat to the opponent.
 *
 * @param pos (const *BOARD) the position
 * @param list (*MOVELIST) the move list to append the move
 * @param move the move to be added to the move list
 *
 * @return static void
 */
static void addCaptureMove (const BOARD *pos, MOVELIST *list, int move);

/**
 * @brief add an en passant move to the move list.
 *
 * a move is considered quiet if it's not a capture, not a check or not a significant threat to the opponent.
 *
 * @param pos (const *BOARD) the position
 * @param list (*MOVELIST) the move list to append the move
 * @param move the move to be added to the move list
 *
 * @return static void
 */
static void addEnPassantMove (const BOARD *pos, MOVELIST *list, int move);

/**
 * @brief add a pawn move to the move list.
 *
 * @param pos (const *BOARD) the position in which a move is made
 * @param from  the square from which a move is made
 * @param to  the square to which a move is made
 * @param capture  the captured piece (if so)
 * @param list (*MOVELIST) the list append the move to
 *
 * @return static void
 */
static void addPawnMove (const BOARD *pos, int from, int to, MOVELIST *list);

/**
 * @brief add a pawn capture move the the move list.
 *
 * @param pos (const *BOARD) the position in which a move is made
 * @param from  the square from which a move is made
 * @param to  the square to which a move is made
 * @param capture  the captured piece (if so)
 * @param list (*MOVELIST) the list append the move to
 *
 * @return static void
 */
static void addPawnCaptureMove (const BOARD *pos, int from, int to, int capture, MOVELIST *list);

/**
 * @brief generate moves for white pawns.
 *
 * @param pos (const *BOARD) the position to generate the moves for
 * @param list (*MOVELIST) the list append the moves to
 *
 * @return static void
 */
static void generateWhitePawnMoves (const BOARD *pos, MOVELIST *list);

/**
 * @brief generate moves for black pawns.
 *
 * @param pos (const *BOARD) the position to generate the moves for
 * @param list (*MOVELIST) the list append the moves to
 *
 * @return static void
 */
static void generateBlackPawnMoves (const BOARD *pos, MOVELIST *list);

/**
 * @brief generate moves for sliding pieces of the side to make a move.
 *
 * @param pos (const *BOARD) the position to generate the moves for
 * @param list (*MOVELIST) the list append the moves to
 *
 * @return static void
 */
static void generateSlidingPieceMoves (const BOARD *pos, MOVELIST *list);

/**
 * @brief generate moves for non-sliding pieces of the side to make a move.
 *
 * @param pos (const *BOARD) the position to generate the moves for
 * @param list (*MOVELIST) the list append the moves to
 *
 * @return static void
 */
static void generateNonSlidingPieceMoves (const BOARD *pos, MOVELIST *list);

/**
 * @brief generate castling moves for white.
 *
 * @param pos (const *BOARD) the position to generate the moves for
 * @param list (*MOVELIST) the list append the moves to
 *
 * @return static void
 */
static void generateWhiteCastlingMoves (const BOARD *pos, MOVELIST *list);

/**
 * @brief generate castling moves for black.
 *
 * @param pos (const *BOARD) the position to generate the moves for
 * @param list (*MOVELIST) the list append the moves to
 *
 * @return static void
 */
static void generateBlackCastlingMoves (const BOARD *pos, MOVELIST *list);

/**
 * @brief driver function for move generation. generate moves for the side to make a move.
 *
 * @param pos (const *BOARD) the position to generate the moves for
 * @param list (*MOVELIST) the list append the moves to
 *
 * @return void
 */
void generateAllMoves (const BOARD *pos, MOVELIST *list);

#endif //MILOCHESS_GENERATE_H
