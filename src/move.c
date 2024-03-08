#include <string.h>

#include "move.h"
#include "globals.h"
#include "generate.h"
#include "board.h"
#include "makemove.h"
#include "validate.h"

char *printMove (const int move) {

    static char moveString[6];
    char piece;

    int fileFrom = boardFiles[FROMSQ(move)];
    ASSERT(isFileRankValid(fileFrom));

    int rankFrom = boardRanks[FROMSQ(move)];
    ASSERT(isFileRankValid(rankFrom));

    int fileTo = boardFiles[TOSQ(move)];
    ASSERT(isFileRankValid(fileTo));

    int rankTo = boardRanks[TOSQ(move)];
    ASSERT(isFileRankValid(rankTo));

    int promoted = PROMOTED(move);

    if (promoted) {
        piece = 'q';
        if (isPieceKnight[promoted])
            piece = 'n';
        else if (isPieceBishopOrQueen[promoted] && !isPieceRookOrQueen[promoted])
            piece = 'b';
        else if (isPieceRookOrQueen[promoted] && !isPieceBishopOrQueen[promoted])
            piece = 'r';
    }

    sprintf(moveString,"%c%c%c%c", 'a' + fileFrom, '1' + rankFrom, 'a' + fileTo, '1' + rankTo);

    if (promoted) {
        strncat(moveString, &piece, 1);
        moveString[5] = '\0';
    }

    return moveString;
}
/**
 * @brief check if a move exists on a movelist.
 *
 * @param pos (*BOARD) the current position
 * @param move the move to be checked
 *
 * @return (bool) true if a move exists on a movelist
 * @return (bool) false otherwise
 */
bool moveExists (BOARD *pos, const int move) {
    S_MOVELIST movelist[1];
    movelist->count = 0;
    generateAllMoves(pos, movelist);

    for (int i = 0; i < movelist->count; ++i) {
        int analyzedMove = movelist->moves[i].move;

        if (!makeMove(pos, analyzedMove))
            continue;
        takeBackMove(pos);
        if (analyzedMove == move)
            return true;
    }

    return false;
}

/**
 * @brief print a move list.
 *
 * @param list (const *S_MOVELIST) the move list to be printed
 *
 * @return void
 */
void printMoveList (const S_MOVELIST *list) {

    int move = 0;
    int score = 0;

    printf("Move list:\n");

    for (int i = 0; i < list->count; ++i) {
        move = list->moves[i].move;
        score = list->moves[i].score;
        printf("Move %d: %s (score %d)\n", i+1, printMove(move), score);
    }

    printf("%d moves total\n", list->count);
}



