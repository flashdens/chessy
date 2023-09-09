#include <stdbool.h>

#include "search.h"
#include "board.h"
#include "utils.h"

/**
 * @brief check if a move is a repetition, based on the position key history.
 *
 * @param pos the current position
 *
 * @return (bool) true if the move is a repetition
 * @return (bool) false otherwise
 */
bool isRepetition (BOARD *pos) {


    for (int i = pos->hisPly - pos->fiftyMove; i < pos->hisPly - 1; ++i) {
        ASSERT(i >= 0 && i < MAX_MOVES);
        if (pos->posKey == pos->history[i].posKey)
            return true;
    }

    return false;
}