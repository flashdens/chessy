#include <stdio.h>
#include <stdlib.h>

#include "init.h"
#include "enums.h"
#include "board.h"
#include "bitboards.h"
#include "utils.h"

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

int main() {
    initAll();

    BOARD board[1];

    parseFen(START_FEN, board);
    printBoard(board);
    printf("\nwhite pawns\n");
    printBitboard(board->pawns[WHITE]);
    printf("\nblack pawns\n");
    printBitboard(board->pawns[BLACK]);
    printf("\nboth pawns\n");
    printBitboard(board->pawns[BOTH]);


    ASSERT(assertBoard(board) == 0);

    return 0;
}
