#include "string.h"

#include "io.h"
#include "data.h"
#include "validate.h"
#include "globals.h"
#include "move.h"
#include "board.h"
#include "enums.h"
#include "generate.h"
#include "utils.h"

// todo segfaults
int parseMove (char *move, BOARD *pos) {

    if (move[0] > 'h' || move[0] < 'a' ||
    move[1] > '8' || move[1] < '1' ||
    move[2] > 'h' || move[2] < 'a' ||
    move[3] > '8' || move[3] < '1' )
        return false;

    ASSERT(checkBoard(pos));

    int fromSquare = FR2SQ(move[0] - 'a', move[1] - '1');
    int toSquare = FR2SQ(move[2] - 'a', move[3] - '1');

    ASSERT(isSquareOnBoard(fromSquare) && isSquareOnBoard(toSquare));

    MOVELIST movelist[1];
    movelist[0].count = 0;
    generateAllMoves(pos, movelist);

    int currentMove = 0;
    int promotedTo = EMPTY;

    for (int i = 0; i < movelist->count; ++i) {
        currentMove = movelist->moves[i].move;

        if (FROMSQ(currentMove) == fromSquare && TOSQ(currentMove) == toSquare) {
            promotedTo = PROMOTED(currentMove);

            if (promotedTo != EMPTY) {
                if (IS_RQ(promotedTo) && !IS_BQ(promotedTo) && move[4] == 'r')
                    return currentMove;
                else if (!IS_RQ(promotedTo) && IS_BQ(promotedTo) && move[4] == 'b')
                    return currentMove;
                else if (IS_RQ(promotedTo) && IS_BQ(promotedTo) && move[4] == 'q')
                    return currentMove;
                else if (IS_KN(promotedTo) && move[4] == 'n') {
                    return currentMove;
                }
                continue;
            }
            return currentMove;
        }

    }
    return 0;
}
