/**
 * @file board.h
 * @brief contains the BOARD and HISTORY structure and functions which modify them.
 */

#ifndef MILOCHESS_BOARD_H
#define MILOCHESS_BOARD_H

#include <stdlib.h>

#include "globals.h"
#include "utils.h"

typedef struct {
    int move;
    int castlePermission;
    int enPassant;
    int fiftyMove;
    U64 positionKey;
}
HISTORY;

typedef struct {
    HISTORY history[MAX_MOVES];
    int pieces[BOARD_SQUARES];

    int kingSquare[2];

    int sideToMove;
    int enPassant;
    int fiftyMove;

    int numOfPieces[13];

    U64 pawns[3];
    int minPieces[2];
    int majPieces[2];
    int bigPieces[2];
    int material[2];

    int ply;
    int hisPly;

    int castlePermission;

    int pieceList[13][10];

    U64 posKey;
}
BOARD;

/**
 * @brief reset the board to its initial state.
 *
 * @param pos (*BOARD) the board be reset.
 *
 * @return void
*/
void resetBoard (BOARD *pos);

/**
 * @brief parse a fen.
 *
 * @param fen (*const char) FEN notation string to be parsed (https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation)
 * @param pos (*BOARD) the board to store the parsing result
 *
 * @return 0 on success.
 * @return 1 on fail with a relevant message.
 */
int parseFen (const char *fen, BOARD *pos);


/**
 * @brief print board to the screen.
 *
 * @param pos (const *BOARD) the board to be printed
 *
 * @return void
 */
void printBoard (const BOARD *pos);

/**
 * @brief update material piece lists.
 *
 * @param pos (*BOARD) the position to have the lists updated.
 *
 * @return void
 */
void updateMaterialLists (BOARD *pos);

/**
* @brief assert if the board structure contains correct information about the board.
*
* @param pos (*const BOARD) the position to be checked.
*
* @return 0 on success
* @return program exit with code 1 on failure
*/
bool assertBoard (const BOARD *pos);



#endif //MILOCHESS_BOARD_H
