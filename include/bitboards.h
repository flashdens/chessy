#include "globals.h"
#include "utils.h"

#ifndef MILOCHESS_BITBOARD_H
#define MILOCHESS_BITBOARD_H

extern void printBitboard(U64 bb);

extern int popBit (U64 *bb);

int countBits (U64 bb);

extern void clearBit(U64 *bb, U64 sq);

extern void setBit(U64 *bb, U64 sq);

#endif
