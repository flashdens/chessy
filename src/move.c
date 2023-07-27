#include <string.h>

#include "move.h"
#include "globals.h"

char *printMove (const int move) {

    static char moveString[6];
    char piece;

    int fileFrom = boardFiles[FROMSQ(move)];
    int rankFrom = boardRanks[FROMSQ(move)];
    int fileTo = boardFiles[TOSQ(move)];
    int rankTo = boardFiles[TOSQ(move)];

    int promoted = PROMOTED(move);

    if (promoted) {
        piece = 'q';
        if (isPieceKnight[promoted])
            piece = 'k';
        else if (isPieceBishopOrQueen[promoted] && !isPieceRookOrQueen[promoted])
            piece = 'b';
        else if (isPieceRookOrQueen[promoted] && !isPieceBishopOrQueen[promoted])
            piece = 'r';
    }

    sprintf(moveString,"%c%c%c%c", 'a' + fileFrom, '1' + rankFrom, 'a' + fileTo, '1' + rankTo);
    if (promoted)
        strcat(moveString, &piece);

    return moveString;
}