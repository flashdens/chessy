#include <stdio.h>
#include <time.h>
#include "utils.h"
#include "perft.h"
#include "board.h"
#include "move.h"
#include "makemove.h"
#include "generate.h"

void perft (BOARD *pos, int depth, long *leafNodes) {
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

void perftTest (BOARD *pos, int depth) {

    ASSERT(checkBoard(pos));

    clock_t startTime, endTime;
    MOVELIST movelist[1];
    movelist[0].count = 0;
    long leafNodes = 0;
    long cumNodes;
    long oldNodes;
    int move;

    printf("Starting perft test with depth %d\n\n", depth);
    startTime = clock();

    generateAllMoves(pos, movelist);

    for (int i = 0; i < movelist->count; ++i) {
        move = movelist->moves[i].move;
        if (!makeMove(pos, move))
            continue;

        cumNodes = leafNodes;
        perft(pos, depth - 1, &leafNodes);
        takeBackMove(pos);
        oldNodes = leafNodes - cumNodes;
        printf("Move %d: %s: %ld\n", i + 1, printMove(move), oldNodes);
    }

    endTime = clock();
    printf("Test complete - visited %ld nodes in %f ms\n", leafNodes, ((double)(endTime - startTime) / CLOCKS_PER_SEC));
}
