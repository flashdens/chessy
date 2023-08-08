/**
 * @file perft.c
 * @brief contains functions needed for move generation testing (perft testing, @see https://www.chessprogramming.org/Perft)
 */
#include <stdio.h>
#include <time.h>

#include "utils.h"
#include "perft.h"
#include "board.h"
#include "move.h"
#include "makemove.h"
#include "generate.h"

long leafNodes = 0;

/**
 * @brief recursively calculate the number of leaf nodes in a move tree.
 *
 * @param pos
 * @param depth the depth of the perft test. once it reaches 0, it returns.
 *
 * @return void (recursive!)
 */
void perft (BOARD *pos, int depth) {
    ASSERT(checkBoard(pos));

    if (depth == 0) {
        leafNodes++;
        return;
    }

    MOVELIST movelist[1];
    movelist[0].count = 0;

    generateAllMoves(pos, movelist);

    for (int i = 0; i < movelist->count; ++i) {
        if (!makeMove(pos, movelist->moves[i].move))
            continue;

        perft(pos, depth - 1);
        printf("%d\n", movelist->moves[i].move);
        printf("%s\n", printMove(movelist->moves[i].move));
        takeBackMove(pos);
    }
}

void perftTest (BOARD *pos, int depth) {

    ASSERT(checkBoard(pos));

    MOVELIST movelist[1]; movelist[0].count = 0;// a temporary workaround?
    long cumNodes = 0; // cumulative nodes
    long oldNodes = 0;
    int move = 0;


    printf("starting perft test with depth %d!\n\n", depth);
    struct timespec start_time, end_time;
    generateAllMoves(pos, movelist);
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < movelist->count; ++i) {
        move = movelist->moves[i].move;
        if (!makeMove(pos, movelist->moves[i].move))
            continue;

        cumNodes = leafNodes;
        perft(pos, depth - 1);
        takeBackMove(pos);
        oldNodes = leafNodes - cumNodes;
        printf("move %d: %s: %ld\n", i + 1, printMove(move), oldNodes);
    }

    printf("test complete - visited %ld nodes in %ld ms", leafNodes, (end_time.tv_sec - start_time.tv_sec) +
                                                                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9);
}


