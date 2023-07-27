#include <stdio.h>
#include <stdlib.h>

#include "move.h"
#include "utils.h"
#include "init.h"
#include "enums.h"

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"

int main() {
    initAll();

        int move = 0;
        int from = A2;
        int to = H7;
        int captured = R;
        int prom = K;

        move = ( ( from ) | ( to << 7 ) | (captured << 14) | (prom << 20) );

        printf("decimal: %d \n hexadecimal: %X\n\n", move, move);
        printBinaryNumber(move);

        printf("%d\n%d\n%d\n%d\n%s\n", FROMSQ(move), TOSQ(move), CAPTURED(move), PROMOTED(move),(move & ISPROMOTION) ? "Y":"N");

    printf("From: %s\n", printSquare(from));
    printf("To: %s\n", printSquare(to));
    printf("Move: %s\n", printMove(move));

    return 0;
}
