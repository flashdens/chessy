#include <stdbool.h>

#include "milochess.h"


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
 * @param pos (*BOARD) the current position
 * @param info (*S_SEARCHINFO) search informations
 *
 * @return void
 */
void clearForSearch(BOARD *pos, S_SEARCHINFO *info) {
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

    info->fh = 0;
    info->fhf = 0;
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

        printf("depth: %d, score %d, move: %s, nodes: %ld ",
               depth,
               bestScore,
               printMove(bestMove),
               info->nodes);

        printf("pv:");
        for (int i = 0; i < pvMoves; ++i) {
            printf(" %s", printMove(pos->pvArray[i]));
        }
        printf(" ordering: %.2f\n", info->fhf / info->fh);
    }

}

static int quiescence(int a, int b, BOARD *pos, S_SEARCHINFO *info) {
    return 0;
}

int alphaBeta(int a, int b, int depth, BOARD *pos, S_SEARCHINFO *info, bool doNull) {
    ASSERT(checkBoard(pos));

    if (depth == 0) {
        info->nodes++;
        return evalPosition(pos);
    }

    info->nodes++;

    // check for a draw
    if (isRepetition(pos) || pos->fiftyMove >= 100)
        return 0;

    // check if the search is not off-limit
    if (pos->ply > MAX_DEPTH - 1) {
        return evalPosition(pos);
    }

    S_MOVELIST movelist[1];
    generateAllMoves(pos, movelist);

    int legalMoves = 0;
    int oldA = a;
    int bestMove = NOMOVE;
    int moveScore = -INFINITE;

    for (int i = 0; i < movelist->count; ++i) {

        // illegal move
        if (!makeMove(pos, movelist->moves[i].move)) {
            continue;
        }

        legalMoves++;
        moveScore = -alphaBeta(-b, -a, depth - 1, pos, info, true);
        takeBackMove(pos);

        if (moveScore > a) {
            if (moveScore >= b) {
                if (legalMoves == 1) {
                    info->fhf++;
                }
                info->fh++;
                return b;
            }
            a = moveScore;
            bestMove = movelist->moves[i].move;
        }
    }

    // if there are no legal moves for a side, then the position is a stale- or checkmate
    if (!legalMoves)
        isSquareAttacked(pos->kingSquare[pos->sideToMove],pos->sideToMove ^ 1, pos)
        ? -INFINITE + pos->hisPly
        : 0;

    if (a != oldA)
        pvtInsert(pos, bestMove);

    return a;
}