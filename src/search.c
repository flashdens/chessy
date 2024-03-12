#include <stdbool.h>

#include "milochess.h"

#define INFINITE 30000

/**
 * @brief check if a move is a repetition, based on the position key history.
 *
 * @param pos the current position
 *
 * @return (bool) true if the move is a repetition
 * @return (bool) false otherwise
 */
bool isRepetition (BOARD *pos) {
    for (int i = pos->hisPly - pos->fiftyMove; i < pos->hisPly - 1; ++i) {
        ASSERT(i >= 0 && i < MAX_MOVES);
        if (pos->posKey == pos->history[i].posKey)
            return true;
    }

    return false;
}

/**
 * @brief prepare the BOARD and SEARCHINFO structures for search .
 *
 * @param  pos (*BOARD) the current position
 * @param info (*S_SEARCHINFO) search informations
 *
 * @return void
 */
static void clearForSearch(BOARD *pos, S_SEARCHINFO *info) {
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < BOARD_SQUARES; ++j) {
            pos->searchHistory[i][j] = 0;
        }
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < MAX_DEPTH; ++j) {
            pos->searchKillers[i][j] = 0;
        }
    }

    pvtClear(pos);
    pos->ply = 0;

    struct timeval t;

    info->startTime = t.tv_sec * 1000 + t.tv_usec / 1000;
    info->nodes = 0;
    info->stopped = false;
}

void searchPosition(BOARD *pos, S_SEARCHINFO *info) {
    int bestMove = NOMOVE;
    int bestScore = -INFINITE;
    int pvMoves = 0;
    clearForSearch(pos, info);

    for (int depth = 1; depth <= info->depth; depth++) {
        bestScore = alphaBeta(-INFINITE,
                              INFINITE,
                              depth,
                              pos,
                              info,
                              true);

        pvMoves = getPVLine(depth, pos);
        bestMove = pos->pvArray[0];

        printf("depth: %d, score %d, move: %s, nodes: %ld",
               depth,
               bestScore,
               printMove(bestMove),
               info->nodes);

        printf("pv:");
        for (int i = 0; i < pvMoves; ++i) {
            printf(" %s", printMove(pos->pvArray[i]));
        }
        printf("\n");


    }


}
static int quiescence(int a, int b, BOARD *pos, S_SEARCHINFO *info) {
    return 0;
}

static int alphaBeta(int a, int b, int depth, BOARD *pos, S_SEARCHINFO *info, bool doNull) {
    return 0;
}