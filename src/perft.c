#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

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
    printf("Test complete - found %ld nodes in %f s\n", leafNodes, ((double)(endTime - startTime) / CLOCKS_PER_SEC));
}

/**
 *
 * @brief perft-test against a set of results stored in a text file.
 *
 * @param argc argument count
 * @param argv arguments
 *
 * @return 0 on success
 * @return 1 on failure, alongside relevant information
 */
int perftHub (int argc, int **argv) {

    printf("welcome to perfthub!\nenter a command below or type help for help\n");
    FILE* input = fopen("perft.txt", "r");

    if (!input) {
        printf("perft.txt not found. do you wish to download it (y/n)?\n");

        char choice;
        scanf(" %c", &choice);

        if (choice != 'y' && choice != 'Y') {
            printf("file download rejected. exiting perfthub...\n");
            return 1;
        }

        int result;
        char command[100] = "wget ";
        const char *url = "https://wierzba.wzks.uj.edu.pl/~21_bogacz/milochess/perft.txt";

        strncat(command, url, strlen(url));
        result = system(command);
        printf("%s\n", command);

        if (result == 0) {
            printf("perft.txt downloaded successfully\n");
        }
        else {
            printf("failed to download perft.txt. exiting perfthub...");
            return 1;
        }
    }

    printf("gimme def (2-7)\n");
    while (1) {
        int depth;
        scanf(" %d", &depth);

        if (depth < 2 || depth > 7)
            printf("please provide a valid number\n");
        else
            break;
    }

    int lines = 0;
    char buf[256];

    while (fgets(buf, sizeof(buf), input) != NULL) {
        printf("Read line: %s", buf);
        lines++;
    }

    rewind(input);

    BOARD board[1];
    char *fen = strtok(buf, ",");
    parseFen()



    return 0;
}