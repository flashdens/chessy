//
// Created by miloszek on 08/09/23.
//

#ifndef MILOCHESS_SEARCH_H
#define MILOCHESS_SEARCH_H

#include "board.h"

#define INFINITE 30000

typedef struct {
    long startTime;
    long stopTime;
    int depth;
    int depthset;
    int timeset;
    int movesToGo;

    long nodes;

    bool infinite;
    bool quit;
    bool stopped;

    float fh;
    float fhf;

} S_SEARCHINFO;

static void checkUp() {}

bool isRepetition(BOARD *pos);

void clearForSearch(BOARD *pos, S_SEARCHINFO *info);

void searchPosition(BOARD *pos, S_SEARCHINFO *info);

static int quiescence(int a, int b, BOARD *pos, S_SEARCHINFO *info);

static int alphaBeta(int a, int b, int depth, BOARD *pos, S_SEARCHINFO *info, bool doNull);


#endif //MILOCHESS_SEARCH_H
