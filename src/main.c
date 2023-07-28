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

int main() {
    initAll();

    BOARD board [1];

    parseFen(FEN5, board);
    printBoard(board);

    MOVELIST movelist [1];

    generateAllMoves(board, movelist);

    printMoveList(movelist);

    return 0;
}
