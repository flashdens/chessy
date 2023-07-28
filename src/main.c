#include <stdio.h>
#include <stdlib.h>

#include "move.h"
#include "utils.h"
#include "init.h"
#include "enums.h"
#include "board.h"
#include "generate.h"

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
#define TEST1 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

int main() {
    initAll();

    BOARD board [1];

    parseFen(TEST1, board);
    printBoard(board);

    MOVELIST movelist [1];

    generateAllMoves(board, movelist);

    printMoveList(movelist);

    return 0;
}
