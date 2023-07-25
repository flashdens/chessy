#ifndef MILOCHESS_GLOBALS_H
#define MILOCHESS_GLOBALS_H

#include "utils.h"

#define BOARD_SQUARES 120
#define MAX_MOVES 2048

extern int Sq120ToSq64[BOARD_SQUARES];
extern int Sq64ToSq120[64];

extern U64 setMask[64];
extern U64 clearMask[64];

extern U64 pieceKeys[13][120];
extern U64 sideKey;
extern U64 castleKeys[16];

extern char pieceChar[];
extern char sideChar[];
extern char rankChar[];
extern char fileChar[];

extern int pieceMin[13];
extern int pieceBig[13];
extern int pieceMaj[13];
extern int pieceVal[13];
extern int pieceCol[13];

#endif
