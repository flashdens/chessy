#include "board.h"
#include "move.h"

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

void generateAllMoves (const BOARD *pos, MOVELIST *list);



#endif //MILOCHESS_GENERATE_H
