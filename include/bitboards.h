#include "macros.h"

#ifndef MILOCHESS_BITBOARD_H
#define MILOCHESS_BITBOARD_H

const int bitTable[64];

extern void printBitboard(U64 bb);

extern int popBit (U64 *bb);

int countBits (U64 bb);

#endif
