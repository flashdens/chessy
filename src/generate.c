#include "generate.h"

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
void addQuietMove (const BOARD *pos, MOVELIST *list, int move) {
    list->moves[list->count].info = move;
    list->moves[list->count].score = 0;
    list->count++;
}

void addCaptureMove (const BOARD *pos, MOVELIST *list, int move) {
    list->moves[list->count].info = move;
    list->moves[list->count].score = 0;
    list->count++;
}

void addEnPassantMove (const BOARD *pos, MOVELIST *list, int move) {
    list->moves[list->count].info = move;
    list->moves[list->count].score = 0;
    list->count++;
}

void generateAllMoves (const BOARD *pos, MOVELIST *list) {

}
