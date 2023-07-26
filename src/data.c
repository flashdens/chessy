#include <stdbool.h>

#include "data.h"
#include "enums.h"

char pieceChar[] = ".PNBRQKpnbrqk";
char sideChar[] = "wb-";
char rankChar[] = "12345678";
char fileChar[] = "abcdefgh";

bool isPieceMin[13] = {false,
                    false,
                    true, true,
                    false, false, false,
                    false,
                    true, true,
                    false, false, false};

bool isPieceBig[13] = {false,
                    false,
                    true, true, true, true, true,
                    false,
                    true, true, true, true, true};

bool isPieceMaj[13] = {false,
                    false, false, false,
                    true, true, true,
                    false, false, false,
                    true, true, true};

int pieceVal[13] = {0,
                    100, 325, 325, 550, 1000, 50000,
                    100, 325, 325, 550, 1000, 50000};

int pieceCol[13] = {BOTH,
                    WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
                    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK};

const int knightDir[8] = { -8, -19,	-21, -12, 8, 19, 21, 12 };
const int rookDir[4] = { -1, -10,	1, 10 };
const int bishopDir[4] = { -9, -11, 11, 9 };
const int kingDir[8] = { -1, -10,	1, 10, -9, -11, 11, 9 };


bool isPiecePawn[13] = { false,
                      true,
                      false, false, false, false, false,
                      true,
                      false, false, false, false, false };

bool isPieceKnight[13] = { false, false,
                        true,
                        false, false, false, false,
                        false,
                        true,
                        false, false, false, false };


bool isPieceRookOrQueen[13] = { false,
                             false, false, false,
                             true, true,
                             false,
                             false, false, false,
                             true, true,
                             false };

bool isPieceBishopOrQueen[13] = { false,
                                 false, false,
                                 true,
                                 false,
                                 true,
                                 false,
                                 false, false,
                                 true,
                                 false,
                                 true,
                                 false };

bool isPieceKing[13] = { false,
                      false, false, false, false, false,
                      true,
                      false, false, false, false, false,
                      true};

int pieceSlides[13] = { false, false, false, true, true, true, false, false, false, true, true, true, false };