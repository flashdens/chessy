#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <perfthub.h>

#include "utils.h"
#include "perft.h"
#include "board.h"
#include "move.h"
#include "makemove.h"
#include "generate.h"

void perft (BOARD *pos, int depth, U64 *leafNodes) {
    ASSERT(checkBoard(pos));

    if (depth == 0) {
        (*leafNodes)++;
        return;
    }

    MOVELIST movelist[1];
    movelist[0].count = 0;

    generateAllMoves(pos, movelist);

    for (int i = 0; i < movelist->count; ++i) {
        if (!makeMove(pos, movelist->moves[i].move))
            continue;
        perft(pos, depth - 1, leafNodes);
        takeBackMove(pos);
    }
}

U64 perftTest (BOARD *pos, int depth, FILE *phubOut) {

    ASSERT(checkBoard(pos));

    MOVELIST movelist[1];
    movelist[0].count = 0;
    U64 leafNodes = 0;
    U64 cumNodes;
    U64 oldNodes;
    int move;

    generateAllMoves(pos, movelist);

    for (int i = 0; i < movelist->count; ++i) {
        move = movelist->moves[i].move;
        if (!makeMove(pos, move))
            continue;

        cumNodes = leafNodes;
        perft(pos, depth - 1, &leafNodes);
        takeBackMove(pos);
        oldNodes = leafNodes - cumNodes;
        if (phubOut)
            fprintf(phubOut, "Move %d: %s: %llu\n", i + 1, printMove(move), oldNodes);
    }

    return leafNodes;
}

