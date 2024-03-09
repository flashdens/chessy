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

static void checkUp() {}

static bool isRepetition(BOARD *pos);

static void clearForSearch(BOARD *pos, S_SEARCHINFO *info);

static void searchPosition(BOARD *pos, S_SEARCHINFO *info);

static int quiescence(int a, int b, BOARD *pos, S_SEARCHINFO *info);

static int alphaBeta(int a, int b, int depth, BOARD *pos, S_SEARCHINFO *info, int doNull);


#endif //MILOCHESS_SEARCH_H
