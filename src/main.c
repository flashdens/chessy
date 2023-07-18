#include <stdio.h>

#include "init.h"
#include "enums.h"
#include "board.h"
#include "bitboards.h"

int main() {
    initAll();

    U64 bitboard = 0ULL;

    bitboard |= (1ULL << SQ64(D2));
    bitboard |= (1ULL << SQ64(D3));
    bitboard |= (1ULL << SQ64(D4));

    printBitboard(bitboard);

    printf("it works!");
    return 0;
}
