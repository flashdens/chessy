#include <stdio.h>

#include "globals.h"
#include "utils.h"
#include "init.h"
#include "enums.h"

int Sq64ToSq120[64];
int Sq120ToSq64[BOARD_SQUARES];

U64 setMask[64];
U64 clearMask[64];

U64 pieceKeys[13][120];
U64 sideKey;
U64 castleKeys[16];

int boardFiles[BOARD_SQUARES];
int boardRanks[BOARD_SQUARES];

/**
 * @brief fill key arrays with random values.
 *
 * @return void
 */
void initHashKeys () {
    for (int i = 0; i < 13; ++i) {
        for (int j = 0; j < 120; ++j) {
            pieceKeys[i][j] = generateRandomU64();
        }
    }

    sideKey = generateRandomU64();

    for (int i = 0; i < 16; ++i) {
        castleKeys[i] = generateRandomU64();
    }
}

/**
 * @brief initialize the 64sq to 120sq and 120sq to 64sq conversion arrays.
 *
 * @return void
 */
void initBitMasks () {
    for (int i = 0; i < 64; ++i) {
        setMask[i] = 0ULL;
        clearMask[i] = 0ULL;
    }

    for (int i = 0; i < 64; ++i) {
        setMask[i] = (1ULL << i);
        clearMask[i] = ~setMask[i];
    }
}

/**
 * @brief fill the 64sq to 120sq and 120sq to 64sq conversion arrays.
 *
 * @return void
 */
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

void initBoardFilesRanks () {

    int square = A1;
    int square64 =  0;

    for (int i = 0; i < BOARD_SQUARES; ++i) {
        boardFiles[i] = OFF_BOARD;
        boardRanks[i] = OFF_BOARD;
    }
}

/**
 * @brief initialize the engine.
 *
 * @return void
 */
void initAll() {
    initBitMasks();
    initHashKeys();
    initSq120To64();
    initBoardFilesRanks();
}