#include <stdio.h>
#include <stdlib.h>

#include "init.h"
#include "enums.h"
#include "board.h"
#include "bitboards.h"
#include "utils.h"

int main() {

    initAll();

    BOARD board[1];

    parseFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", board);
    printBoard(board);
    parseFen("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1", board);
    printBoard(board);
    parseFen("4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk - 0 1", board);
    printBoard(board);
    printf("it works!");
    return 0;
}
