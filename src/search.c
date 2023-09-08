#include <stdbool.h>

#include "search.h"
#include "board.h"

bool isRepetition (BOARD *pos) {

    for (int i = pos->hisPly - pos->fiftyMove; i < pos->hisPly-1; ++i) {
        if (pos->posKey == pos->history[i].posKey)
            return true;
    }

    return false;
}