//
// Created by miloszek on 08/09/23.
//

#ifndef MILOCHESS_SEARCH_H
#define MILOCHESS_SEARCH_H

#include "board.h"

typedef struct {
    int startTime;
    int stopTime;
    int depth;
    int depthset;
    int timeset;
    int movesToGo;

    long nodes;

    bool infinite;
    bool quit;
    bool stopped;

} S_SEARCHINFO;

static bool isRepetition (BOARD *pos);

#endif //MILOCHESS_SEARCH_H
