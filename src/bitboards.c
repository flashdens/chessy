#include <stdio.h>

#include "enums.h"
#include "macros.h"

void printBitboard (unsigned long long board) {

    U64 shifter = 1ULL;

    int square;
    int square64;

    for (int rank = RANK_8; rank >= RANK_1; --rank) {
        for (int file = FILE_A; file <= FILE_H; ++file) {
            square = FR2SQ(file, rank);
            square64 = SQ64(square);
            if ((shifter << square64) & board)
                printf("X");
            else
                printf("-");
        }
        printf("\n");
    }
}