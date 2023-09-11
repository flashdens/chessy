#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "move.h"
#include "utils.h"
#include "init.h"
#include "attack.h"
#include "board.h"
#include "enums.h"
#include "generate.h"
#include "perfthub.h"
#include "makemove.h"
#include "search.h"
#include "io.h"
#include "pvtable.h"

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define FEN5 "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define FEN6 "rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b KQkq e3 0 1"
#define FEN7 "5k2/1n6/4n3/6N1/8/3N4/8/5K2 b - - 0 1"
#define ROOKS "6k1/8/5r2/8/1nR5/5N2/8/6K1 b - - 0 1"
#define QUEENS "6k1/8/4nq2/8/1nQ5/5N2/1N6/6K1 b - - 0 1"
#define BISHOPS "6k1/1b6/4n3/8/1n4B1/1B3N2/1N6/2b3K1 b - - 0 1"
#define WCASTLE "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"
#define BCASTLE "r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1"
#define KIWIPETE "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define PROMOTION "8/3P4/8/k3K3/8/8/1p6/8 w - - 0 1"



int main() {
    initAll();

    BOARD board[1];
    MOVELIST movelist[1];
    PVTABLE table[1];

    parseFen(PROMOTION, board);

    char input[6];
    int currentMove = 0;

    pvtProbe(table, board);

//    while (1) {
//        printBoard(board);
//        printf("provide a move\n");
//        fgets(input, sizeof(input),stdin);
//        fflush(stdin);
//
//        if (input[0] == 'q') {
//            break;
//        }
//        else if (input[0] == 't') {
//            takeBackMove(board);
//            continue;
//        }
//        else {
//            currentMove = parseMove(input, board);
//            if (currentMove != 0) {
//                makeMove(board, currentMove);
//                if (isRepetition(board))
//                    printf("repetition detected\n");
//            }
//            else
//                printf("invalid move\n");
//        }
//
//    }
//
//    BOARD board[1];
//    MOVELIST movelist[1];
//
//    parseFen(KIWIPETE, board);
//
//    char *simulated_argv[] = {
//            "perfthub",
//            "-s",
//            "-e"
//    };
//    char** argv = (char **) malloc(sizeof(char *) * 3);
//
//    for (int i = 0; i < 3; ++i) {
//        argv[i] = (char *)malloc(strlen(simulated_argv[i]) + 1);
//        strcpy(argv[i], simulated_argv[i]);
//    }
//
//    perfthub(3, argv);
//
//    free(argv);

    return 0;
}
