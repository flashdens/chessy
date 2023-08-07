#ifndef MILOCHESS_MOVE_H
#define MILOCHESS_MOVE_H

#include "globals.h"

// macros to help reading the bits from MOVE->move.

/** @brief from square */
#define FROMSQ(m) ((m) & 0x7F)

/** @brief to square */
#define TOSQ(m) (((m)>>7) & 0x7F)

/** @brief captured piece (if so) */
#define CAPTURED(m) (((m)>>14) & 0xF)

/** @brief promoted to piece (if so) */
#define PROMOTED(m) (((m)>>20) & 0xF)

/** @brief (flag) is the move en passant? */
#define FISENPASSANT 0x40000

/** @brief (flag) is the move a pawn start? */
#define FISPAWNSTART 0x80000

/** @brief (flag) is the move a castle? */
#define FISCASTLE 0x1000000

/** @brief (flag) is the move a capture? */
#define FISCAPTURE 0x7C000

/** @brief (flag) is the move a promotion? */
#define FISPROMOTION 0xF00000


/**
 * @struct MOVE
 *
 * @brief a structure representing moves.
 *
 * @param move the information about the move is stored as a 32-bit integer, though only 25 bits are used.
 * @param score the score of the move.
 *
 * the MOVE->move bits correspond to:
 *
 * 0000 0000 0000 0000 0000 0000 0|111 1111| - the square FROM which a move is made (0x7F, bits 1-7)
 * 0000 0000 0000 0000 00|11 1111 1|000 0000 - the square TO which a move is made (7 >> 0x7F, bits 8-14)
 * 0000 0000 0000 00|11 11|00 0000 0000 0000 - the piece captured by the move (if so) (14 >> 0xF, bits 15-18)
 * 0000 0000 0000 0|1|00 0000 0000 0000 0000 - was the capture en passant? (0x4000, bit 19)
 * 0000 0000 0000 |1|000 0000 0000 0000 0000 - was this move a pawn start? (0x8000, bit 20)
 * 0000 0000 |1111| 0000 0000 0000 0000 0000 - if it was a promotion move, which piece did the pawn get promoted to? (20 >> 0xF, bits 21-24)
 * 0000 000|1| 0000 0000 0000 0000 0000 0000 - is this a castle? (0x1000000, bit 25)
 * |0000 000|1 0000 0000 0000 0000 0000 0000 - free irrelevant space (25 << 0X7F, bitS 26-32)
 */
typedef struct {
    int move;
    int score;
} MOVE;

/**
 * @struct MOVELIST
 *
 * @param moves (MOVE[MAX_POSITION_MOVES]) the moves available in a position
 * @param count the number of moves in the movelist
 *
 * the list of possible moves.
 *
 */
typedef struct {
    MOVE moves[MAX_POSITION_MOVES];
    int count;
} MOVELIST;


/**
 * @brief print a move list.
 *
 * @param list (const *MOVELIST) the move list to be printed
 *
 * @return void
 */
void printMoveList (const MOVELIST *list);

#endif //MILOCHESS_MOVE_H
