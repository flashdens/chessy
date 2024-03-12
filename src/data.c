#include <stdbool.h>

#include "milochess.h"

//TODO make these consts

const char pieceChar[] = ".PNBRQKpnbrqk";
const char sideChar[] = "wb-";
const char rankChar[] = "12345678";
const char fileChar[] = "abcdefgh";

const bool isPieceMin[13] = {false,
                    false,
                    true, true,
                    false, false, false,
                    false,
                    true, true,
                    false, false, false};

const bool isPieceBig[13] = {false,
                    false,
                    true, true, true, true, true,
                    false,
                    true, true, true, true, true};

const bool isPieceMaj[13] = {false,
                    false, false, false,
                    true, true, true,
                    false, false, false,
                    true, true, true};

const int pieceVal[13] = {0,
                    100, 325, 325, 550, 1000, 50000,
                    100, 325, 325, 550, 1000, 50000};

const int pieceCol[13] = {BOTH,
                    WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
                    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK};

const int knightDir[8] = { -8, -19,	-21, -12, 8, 19, 21, 12 };
const int rookDir[4] = { -1, -10,	1, 10 };
const int bishopDir[4] = { -9, -11, 11, 9 };
const int kingDir[8] = { -1, -10,	1, 10, -9, -11, 11, 9 };


const bool isPiecePawn[13] = { false,
                      true,
                      false, false, false, false, false,
                      true,
                      false, false, false, false, false };

const bool isPieceKnight[13] = { false, false,
                        true,
                        false, false, false, false,
                        false,
                        true,
                        false, false, false, false };


const bool isPieceRookOrQueen[13] = { false,
                             false, false, false,
                             true, true,
                             false,
                             false, false, false,
                             true, true,
                             false };

const bool isPieceBishopOrQueen[13] = { false,
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

const bool isPieceKing[13] = { false,
                      false, false, false, false, false,
                      true,
                      false, false, false, false, false,
                      true};

const bool doesPieceSlide[13] = { false, false, false, true, true, true, false, false, false, true, true, true, false };