#include <stdio.h>

#include "globals.h"
#include "macros.h"
#include "init.h"
#include "enums.h"

int Sq64ToSq120[64];
int Sq120ToSq64[BOARD_SQUARES];

void initSq120To64() {


    int square;
    int square64 = 0;

    for (int i = 0; i < BOARD_SQUARES; ++i) {
        Sq120ToSq64[i] = 65;
    }

    for (int i = 0; i < 64; ++i) {
        Sq64ToSq120[i] = 120;
    }

    for (int rank = RANK_1; rank <= RANK_8; ++rank) {
        for (int file = FILE_A; file <= FILE_H; ++file) {
            square = FR2SQ(file, rank);
            Sq64ToSq120[square64] = square;
            Sq120ToSq64[square] = square64;
            square64++;
        }
    }
}

void initAll() {
    initSq120To64();

    /*
    for (int i = 0; i < 120; ++i) {
        if (i % 10 == 0)
            printf("\n");
        printf("%3d", Sq120ToSq64[i]);
    }
    printf("\n\n");

    for (int i = 0; i < 64; ++i) {
        if (i % 8 == 0)
            printf("\n");
        printf("%5d", Sq64ToSq120[i]);
    }
    */
}