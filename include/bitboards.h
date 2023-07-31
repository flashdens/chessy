#ifndef MILOCHESS_BITBOARD_H
#define MILOCHESS_BITBOARD_H

#include "globals.h"
#include "utils.h"

extern void printBitboard(U64 bb);

extern int popBit (U64 *bb);

int countSetBits (U64 bb);

extern void clearBit(U64 *bb, int sq);

extern void setBit(U64 *bb, U64 sq);

#endif
