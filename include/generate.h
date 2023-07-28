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
#define MOVE(from,to,capture,promote,fl) ( (from) | ((to) << 7) | ( (capture) << 14 ) | ( (promote) << 20 ) | (fl))

#ifndef MILOCHESS_GENERATE_H
#define MILOCHESS_GENERATE_H

/**
 * @brief add a quiet move to the move list.
 *
 * a move is considered quiet if it's not a capture, not a check or not a significant threat to the opponent.
 *
 * @param pos (const *BOARD) the position
 * @param list (*MOVELIST) the move list to append the move
 * @param move the move to be added to the move list
 *
 * @return void
 */
void addQuietMove (const BOARD *pos, MOVELIST *list, int move);

void addCaptureMove (const BOARD *pos, MOVELIST *list, int move);

void addEnPassantMove (const BOARD *pos, MOVELIST *list, int move);

/**
 * @brief add a pawn move to the move list.
 *
 * @param pos (const *BOARD) the position in which a move is made
 * @param from (const) the square from which a move is made
 * @param to (const) the square to which a move is made
 * @param capture (const) the captured piece (if so)
 * @param list (*MOVELIST) the list append the move to
 */
void addPawnMove (const BOARD *pos, int from, int to, MOVELIST *list);

/**
 * @brief add a pawn capture move the the move list.
 *
 * @param pos (const *BOARD) the position in which a move is made
 * @param from (const) the square from which a move is made
 * @param to (const) the square to which a move is made
 * @param capture (const) the captured piece (if so)
 * @param list (*MOVELIST) the list append the move to
 */
void addPawnCaptureMove (const BOARD *pos, int from, int to, int capture, MOVELIST *list);


void generateAllMoves (const BOARD *pos, MOVELIST *list);



#endif //MILOCHESS_GENERATE_H
