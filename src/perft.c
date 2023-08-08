/**
 * @file perft.c
 * @brief contains functions needed for move generation testing (perft testing, @see https://www.chessprogramming.org/Perft)
 */
#include <stdio.h>

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
long perft (BOARD *pos, int depth) {
    ASSERT(checkBoard(pos));

    if (depth == 0) {
        return 1;
    }

    long nodes = 0;
    MOVELIST movelist[1];
    movelist[0].count = 0;

    generateAllMoves(pos, movelist);

    for (int i = 0; i < movelist->count; ++i) {
        printf("%d\n", movelist->moves[i].move);
        if (!makeMove(pos, movelist->moves[i].move))
            continue;

        printf("%ld\n", nodes);
        nodes += perft(pos, depth - 1);
        takeBackMove(pos);
    }

    return nodes;
}

void perftTest (BOARD *pos, int depth) {

    ASSERT(checkBoard(pos));

    MOVELIST movelist[1]; movelist[0].count = 0;// a temporary workaround?
    long cumNodes = 0; // cumulative nodes
    long oldNodes = 0;
    int move = 0;


    printf("starting perft test with depth %d!\n\n", depth);
    generateAllMoves(pos, movelist);

    for (int i = 0; i < movelist->count; ++i) {
        move = movelist->moves[i].move;
        if (!makeMove(pos, movelist->moves[i].move))
            continue;

        cumNodes = leafNodes;
        perft(pos, depth - 1);
        takeBackMove(pos);
        oldNodes = leafNodes - cumNodes;
        printf("move %d: %s : %ld\n", i + 1, printMove(move), oldNodes);
    }

    printf("test complete - visited %ld nodes", leafNodes);
}


